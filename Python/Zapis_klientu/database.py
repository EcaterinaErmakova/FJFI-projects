import sqlite3
from datetime import datetime, time, timedelta
from contextlib import contextmanager
from typing import Generator
from models import Client, Service, Appointment

class Database:
    """ Database handler for client management system """
    def __init__(self, db_name="clients.db") -> None:
        # Define db name.
        self.db_name = db_name
        self._init_db()
    @contextmanager
    def _get_cursor(self) -> Generator[sqlite3.Cursor, None, None]:
        '''
        Create a connection using connect() method and pass the name of the database 
        you want to access if there is a file with that name, it will open that file. 
        Otherwise, Python will create a file with the given name.
        '''
        connectionDB= sqlite3.connect(self.db_name)
        # Cursor object is called to be capable to send commands to the SQL. 
        cursorDB = connectionDB.cursor()
        # Pass the cursorDB back to the caller using yield.
        try:
            # Yields the database cursor to the calling code.
            yield cursorDB
            # To save the changes in the files. 
            connectionDB.commit()
        finally:
            # To close the connection.
            connectionDB.close()    
    def _init_db(self) -> None:
        # Get connection with database to modify it.
        with self._get_cursor() as db:
            # Execute the statement, create a table of clients in the database.
            db.execute('''CREATE TABLE IF NOT EXISTS clients
                         (id INTEGER PRIMARY KEY AUTOINCREMENT,
                          name TEXT NOT NULL,
                          phone TEXT NOT NULL,
                          email TEXT,
                          notes TEXT)''') 
            # Execute the statement, create a table of clients in the database.
            db.execute('''CREATE TABLE IF NOT EXISTS services
                         (id INTEGER PRIMARY KEY AUTOINCREMENT,
                          name TEXT NOT NULL,
                          duration INTEGER NOT NULL,
                          price REAL NOT NULL)''')
            # Execute the statement, create a table of appointments in the database.
            db.execute('''CREATE TABLE IF NOT EXISTS appointments
                         (id INTEGER PRIMARY KEY AUTOINCREMENT,
                          client_id INTEGER NOT NULL,
                          service_id INTEGER NOT NULL,
                          datetime TEXT NOT NULL,
                          status TEXT NOT NULL,
                          FOREIGN KEY(client_id) REFERENCES clients(id),
                          FOREIGN KEY(service_id) REFERENCES services(id))''')

    # clients

    def add_client(self, name: str, phone: str, email: str = "", notes: str = "") -> int:
        # connection with db
        with self._get_cursor() as db:
            # translate from SQL -> Python : insert new Client
            db.execute("INSERT INTO clients (name, phone, email, notes) VALUES (?, ?, ?, ?)", (name, phone, email, notes))
            # return id of new note
            return db.lastrowid
        
    def get_all_clients(self) -> list[Client]:
        # connection with db
        with self._get_cursor() as db:
            # translate from SQL -> Python : show clients (id, name, phone, email, note)
            db.execute("SELECT id, name, phone FROM clients")
            # fetch all rows as a list of tuples
            return [Client(*row) for row in db.fetchall()]

    # services

    def add_service(self, name: str, duration: int, price: float) -> int:
        # connection with db
        with self._get_cursor() as db:
            # translate from SQL -> Python : insert new service
            db.execute("INSERT INTO services (name, duration, price) VALUES (?, ?, ?)", (name, duration, price))
            # return id of new note
            return db.lastrowid
    
    def get_all_services(self) -> list[Service]:
        # connection with db
        with self._get_cursor() as db:
            # translate from SQL -> Python : show services (id, name, duration, price)
            db.execute("SELECT * FROM services")
            # fetch all rows as a list of tuples
            return [Service(*row) for row in db.fetchall()]    

    # appointments

    def add_appointment(self, client_id: int, service_id: int, datetime_str: str, status: str = "planned") -> tuple[int, str]:
        try:
            # str -> datetime
            dt = datetime.fromisoformat(datetime_str)
        except ValueError:
            # if value has right format
            return None, "Invalid datetime format. Use ISO format (YYYY-MM-DD HH:MM)"        
        # if time is not avaible
        if not self._is_time_slot_available(dt, service_id):
            return None, "Time slot not available"
        # connection with db
        with self._get_cursor() as db:
            try:
                # translate from SQL -> Python : insert new appointment
                db.execute("INSERT INTO appointments (client_id, service_id, datetime, status) VALUES (?, ?, ?, ?)", (client_id, service_id, datetime_str, status))
                # return id of new note
                return db.lastrowid, "Appointment added successfully"
            except sqlite3.IntegrityError:
                return None, " Invalid client_id or service_id"
   
    def get_all_appointments(self) -> list[Appointment]:
        # connection with db
        with self._get_cursor() as db:
            # translate from SQL -> Python : show appointments ordered by date and time
            db.execute("SELECT * FROM appointments ORDER BY datetime")
            # fetch all rows as a list of tuples
            return [Appointment(*row) for row in db.fetchall()] 
    
    def get_appointments_by_date(self, date: str) -> list[Appointment]:
        # connection with db
        with self._get_cursor() as db:
            # translate from SQL -> Python : show appointments with given date
            db.execute("SELECT * FROM appointments WHERE date(datetime) = ? ORDER BY datetime", (date,))
            # fetch all rows as a list of tuples
            return [Appointment(*row) for row in db.fetchall()]
    
    def update_appointment_status(self, appointment_id: int, status: str) -> bool:
        # connection with db
        with self._get_cursor() as db:
            # translate from SQL -> Python : change the status of given appointment
            db.execute("UPDATE appointments SET status = ? WHERE id = ?", (status, appointment_id))
            # return True if status was changed
            return db.rowcount > 0
    
    # check if there is already an appointment from the new time on the same date
    def _is_time_slot_available(self, start_time: datetime, service_id: int) -> bool:
        # get service by ID
        service = self.get_service_by_id(service_id)
        if not service:
            return False
        # count possible end of appointment
        end_time = start_time + timedelta(minutes=service.duration)
        # connection with db
        with self._get_cursor() as db:
            # translate from SQL -> Python : find all appointments on the same date as start_time and its service durations
            db.execute('''
                SELECT a.datetime, s.duration 
                FROM appointments a
                JOIN services s ON a.service_id = s.id
                WHERE date(a.datetime) = ?
            ''', (start_time.date().isoformat(),))
            # for each chosen appointments (its datetime and its duration)
            for existing_start_str, existing_duration in db.fetchall():
                # start of existing appointment
                existing_start = datetime.fromisoformat(existing_start_str)
                # end of existing appointment
                existing_end = existing_start + timedelta(minutes=existing_duration)
                # if intervals of time are somehow crossed: -
                if (start_time < existing_end) and (end_time > existing_start):
                    return False
        # if time is available: +
        return True

    # give free times (slots) for appointments on specific date and for specific service
    def get_available_slots(self, date: str, service_id: int) -> list[str]:
        # find needed service
        service = self.get_service(service_id)
        # if this service exists
        if not service:
            return []
        # start of work day
        work_start = datetime.strptime(f"{date} 08:00", "%Y-%m-%d %H:%M")
        # end of work day
        work_end = datetime.strptime(f"{date} 20:00", "%Y-%m-%d %H:%M")
        # interval between 2 slots
        slot_duration = timedelta(minutes=30)
        # get all appointments on given date
        appointments = self.get_appointments_by_date(date)

        slots = []
        # cursor on slots
        current_slot = work_start
        # generate all possible slots
        while current_slot + timedelta(minutes=service.duration) <= work_end:
            slots.append(current_slot)
            current_slot += slot_duration
        
        # find avaible slots
        available_slots = []
        for slot in slots:
            # find the end time of appointment
            end_time = slot + timedelta(minutes=service.duration)
            is_available = True
            
            for app in appointments:
                # start time of existing appointment
                app_start = datetime.fromisoformat(app.datetime)
                # end time of existing appointment
                app_end = app_start + timedelta(minutes=self.get_service(app.service_id).duration)
                # if appointmet time covers slot, then it's not available
                if (slot < app_end) and (end_time > app_start):
                    is_available = False
                    break
            # if it's available
            if is_available:
                available_slots.append(slot.strftime("%Y-%m-%d %H:%M"))
        # return all available slots
        return available_slots

    def get_client_by_id(self, client_id: int) -> Client:
        # conection with db
        with self._get_cursor() as db:
            # translate from SQL -> Python : select client by ID
            db.execute("SELECT id, name, phone FROM clients WHERE id = ?", (client_id,))
            # select 1 row
            row = db.fetchone()
            # return needed row or None
            return Client(*row) if row else None

    def get_service_by_id(self, service_id: int) -> Service:
        # conection with db
        with self._get_cursor() as db:
            # translate from SQL -> Python : select service by ID
            db.execute("SELECT * FROM services WHERE id = ?", (service_id,))
            # select 1 row
            row = db.fetchone()
            # return needed row or None
            return Service(*row) if row else None

    # detete data     
    def delete_client(self, client_id: int) -> bool:
        # conection with db
        with self._get_cursor() as db:
            try:
                # translate from SQL -> Python : delete client by ID
                db.execute("DELETE FROM clients WHERE id = ?", (client_id,))
                # if row was deleted
                if db.rowcount > 0:
                    # reindex the table
                    self.reindex_table('clients')
                    return True
                return False
            except Exception as e:
                print(f"Error deleting client: {str(e)}")
                return False

    def delete_service(self, service_id: int) -> bool:
        # conection with db
        with self._get_cursor() as db:
            try:
                # translate from SQL -> Python : delete service by ID
                db.execute("DELETE FROM services WHERE id = ?", (service_id,))
                # if row was deleted
                if db.rowcount > 0:
                    # reindex the table
                    self.reindex_table('services')
                    return True
                return False
            except Exception as e:
                print(f"Error deleting service: {str(e)}")
                return False

    def delete_appointment(self, appointment_id: int) -> bool:
        # conection with db
        with self._get_cursor() as db:
            try:
                # translate from SQL -> Python : delete appointment by ID
                db.execute("DELETE FROM appointments WHERE id = ?", (appointment_id,))
                if db.rowcount > 0:
                    # reindex the table
                    self.reindex_table('appointments')
                    return True
                return False
            except Exception as e:
                print(f"Error deleting appointment: {str(e)}")
                return False
    
    def reindex_table(self, table_name: str) -> bool:
        # connection with db
        with self._get_cursor() as db:
            try:
                # get all columns (but ID)
                db.execute(f"PRAGMA table_info({table_name})")
                columns = [col[1] for col in db.fetchall() if col[1] != 'id']
                # create table without indexes
                db.execute(f"CREATE TABLE temp_{table_name} AS SELECT * FROM {table_name} WHERE 1=0")
                # translate from SQL -> Python : insert existing data (but indexes)
                db.execute(f"""
                    INSERT INTO temp_{table_name} (id, {', '.join(columns)})
                    SELECT 
                        ROW_NUMBER() OVER (ORDER BY id) AS id,
                        {', '.join(columns)}
                    FROM {table_name}
                """)
                # translate from SQL -> Python : delete previous table
                db.execute(f"DROP TABLE {table_name}")
                # translate from SQL -> Python : save new table
                db.execute(f"ALTER TABLE temp_{table_name} RENAME TO {table_name}")
                # reindex new table
                #self.reset_auto_increment(table_name)
                db.execute(f"DELETE FROM sqlite_sequence WHERE name = '{table_name}'")
                return True
            except Exception as e:
                print(f"Error reindexing {table_name}: {str(e)}")
                return False
    
''' def reset_auto_increment(self, table_name: str):
        with self._get_cursor() as db:
            db.execute(f"DELETE FROM sqlite_sequence WHERE name = '{table_name}'")'''