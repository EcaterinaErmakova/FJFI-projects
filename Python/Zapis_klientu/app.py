from email import message
import sqlite3
from nicegui import ui
from database import Database
from datetime import datetime, timedelta
from models import Client, Service, Appointment
import os
class ManagementApp:
    ''' Define class Database and initialize user interface. '''
    def __init__(self) -> None:
        # creat connection with database 
        self.db = Database()
        self.set_up_ui()
    ''' Create the main application interface. '''
    def set_up_ui(self) -> None:
        # main navigation
        with ui.tabs() as tabs:
            self.clients_tab = ui.tab('Clients') # table of Clients
            self.services_tab = ui.tab('Services') # table of Services
            self.appointments_tab = ui.tab('Appointments') # table of Appointments
        # SQL tables -> NiceGui tables
        # table panels that correspond to the navigation tabs        
        with ui.tab_panels(tabs, value=self.appointments_tab):
            with ui.tab_panel(self.clients_tab): self.set_up_clients_tab()
            with ui.tab_panel(self.services_tab): self.set_up_services_tab()
            with ui.tab_panel(self.appointments_tab): self.set_up_appointments_tab()

    '''_____CLIENTS_____'''
    
    def set_up_clients_tab(self) -> None:
        # form for adding new Client
        with ui.column():
            # !interface detail!
            ui.label('Add New Client') 
            # Client input fields:
            self.client_name = ui.input('Name')
            self.client_phone = ui.input('Phone')
            # add Client with pressing this button
            ui.button('Add', on_click=self.add_client)
            # !interface detail!
            ui.label('Clients List') 
            ''' 
            Clients display table configuration:
            A list of column definitions, where each dictionary defines, 
            what appears as the column header in the table UI (name)
            the name of the key to map from each row of data (field).
            Lable is the name of column (in interface).
            '''
            columns = [
                {'name': 'id', 'label': 'ID', 'field': 'id'},
                {'name': 'name', 'label': 'Name', 'field': 'name'},
                {'name': 'phone', 'label': 'Phone', 'field': 'phone'},
                {'name': 'actions', 'label': 'Actions', 'field': 'actions'}
            ]
            # use defined columns type, starts with an empty table, key column is ID
            self.clients_table = ui.table(columns=columns, rows=[], row_key='id')
            # update table
            self.refresh_clients_table()

    def add_client(self) -> None:
        name = self.client_name.value.strip() # name of client
        phone = self.client_phone.value.strip() # phone of client
        # validity of given data
        if not name or not phone:
            ui.notify("Name and phone are required", type='negative')
            return
        try:
            # add client with given data and with method from database.py
            self.db.add_client(name=name, phone=phone)
            # notification of success
            ui.notify("Client added", type='positive')
            # update table
            self.refresh_clients_table()
            # refresh datas
            self.client_name.value = ""
            self.client_phone.value = ""
            # update the dropdown options for client selection in the appointment 
            self._update_appointment_client_options()
        except sqlite3.Error as e:
            # notification of fail
            ui.notify(f"Database Error: {str(e)}", type='negative')
        except Exception as e:
            # notification of fail
            ui.notify(f"Error: {str(e)}", type='negative')
    
    def refresh_clients_table(self) -> None:
        # list of all clients
        clients = self.db.get_all_clients()
        rows = []
        # create rows of clients
        for cl in clients:
            rows.append({
                'id': cl.id,
                'name': cl.name,
                'phone': cl.phone,
                'actions': None  
            })
        # update rows in table
        self.clients_table.rows = rows
        # save changes
        self.clients_table.update()
        
        # add buttons with slots
        for row in self.clients_table.rows:
            # dynamically inject content into table cells
            with self.clients_table.add_slot('body-cell-actions', row['id']):
                # create new variable binding for each iteration
                with ui.row().classes('p-1 gap-1'):
                    # create delete button
                    ui.button(icon='delete', on_click=lambda _, id=row['id']: self.delete_entity('client', id)).props('flat color=red')
    
    def _update_appointment_client_options(self) -> None:
        # list of clients
        clients = self.db.get_all_clients()
        # create a dictionary of client options for the dropdown
        self.appointment_client.options = {cl.id: f"{cl.name} ({cl.phone})" for cl in clients}
        # force to show the new options
        self.appointment_client.update()

    '''_____SERVICES_____'''
    
    def set_up_services_tab(self) -> None:
        # form for adding new Service
        with ui.column():
            # !interface detail!
            ui.label('Add New Service') 
            # Service input fields:
            self.service_name = ui.input('Name')
            self.service_duration = ui.number('Duration (min)', value=30)
            self.service_price = ui.number('Price', value=50)
            # add Service with pressing this button
            ui.button('Add', on_click=self.add_service)
            # !interface detail!
            ui.label('Services List')
            ''' 
            Services display table configuration:
            A list of column definitions, where each dictionary defines, 
            what appears as the column header in the table UI (name)
            the name of the key to map from each row of data (field).
            Lable is the name of column (in interface).
            '''
            columns = [
                {'name': 'id', 'label': 'ID', 'field': 'id'},
                {'name': 'name', 'label': 'Name', 'field': 'name'},
                {'name': 'duration', 'label': 'Duration', 'field': 'duration'},
                {'name': 'price', 'label': 'Price', 'field': 'price'},
                {'name': 'actions', 'label': 'Actions', 'field': 'actions'}
            ]
            # use defined columns type, starts with an empty table, key column is ID
            self.services_table = ui.table(columns=columns, rows=[], row_key='id')
            # update table
            self.refresh_services_table()

    def add_service(self) -> None:
        name = self.service_name.value.strip() # name of service
        duration = self.service_duration.value # duration of service
        price = self.service_price.value # price of service
        # validity of given data
        if not name or duration <= 0 or price < 0:
            ui.notify("Invalid data", type='negative')
            return
        try:
            # add service with given data and with method from database.py
            self.db.add_service(name=name, duration=int(duration), price=float(price))
            # notification of success
            ui.notify("Service added", type='positive')
            # update table
            self.refresh_services_table()
            # refresh datas
            self.service_name.value = ""
            # update the dropdown options for service selection in the appointment 
            self._update_appointment_service_options()
        except ValueError as e:
            # notification of fail
            ui.notify(f"Invalid input: {str(e)}", type='negative')
        except sqlite3.Error as e:
            # notification of fail
            ui.notify(f"Database error: {str(e)}", type='negative')
        except Exception as e:
            # notification of fail
            ui.notify(f"Error: {str(e)}", type='negative')

    def refresh_services_table(self) -> None:
        # list of all services
        services = self.db.get_all_services()
        rows = []
        # create rows of services
        for s in services:
            rows.append({
                'id': s.id,
                'name': s.name,
                'duration': s.duration,
                'price': f"${s.price:.2f}",
                'actions': None  
            })
        # update rows in table
        self.services_table.rows = rows
        # save changes
        self.services_table.update()
        
        # add buttons with slots
        for row in self.services_table.rows:
            # dynamically inject content into table cells
            with self.services_table.add_slot('body-cell-actions', row['id']):
                # create new variable binding for each iteration
                with ui.row().classes('p-1 gap-1'):
                    # create delete button
                    ui.button(icon='delete', on_click=lambda _, id=row['id']: self.delete_entity('service', id)).props('flat color=red')
    
    def _update_appointment_service_options(self) -> None:
        # list of services
        services = self.db.get_all_services()
        # create a dictionary of services options for the dropdown
        self.appointment_service.options = {ser.id: f"{ser.name} (${ser.price:.2f})" for ser in services}
        # force to show the new options
        self.appointment_service.update()

    '''_____APPOINTMENTS_____'''
    
    def set_up_appointments_tab(self) -> None:
        # form for adding new Appointment
        with ui.column():
            # !interface detail!
            ui.label('Schedule Appointment')
            clients = self.db.get_all_clients() # list of all clients
            services = self.db.get_all_services() # list of all services
            # choose client from given list
            self.appointment_client = ui.select(
                options={cl.id: f"{cl.name} ({cl.phone})" for cl in clients},
                label='Client'
            )
            # choose service from given list
            self.appointment_service = ui.select(
                options={s.id: f"{s.name} (${s.price:.2f})" for s in services},
                label='Service'
            )
            # get only current datetime as a variable
            self.appointment_date = ui.date(value=datetime.now().date())
            self.appointment_time = ui.time(value=datetime.now().time())
            # add appointment with given datas
            ui.button('Book', on_click=self.add_appointment)
            # !interface detail!
            ui.label('Appointments List')
            ''' 
            Appointments display table configuration:
            A list of column definitions, where each dictionary defines, 
            what appears as the column header in the table UI (name)
            the name of the key to map from each row of data (field).
            Lable is the name of column (in interface).
            '''
            columns = [
                {'name': 'id', 'label': 'ID', 'field': 'id'},
                {'name': 'client', 'label': 'Client', 'field': 'client'},
                {'name': 'service', 'label': 'Service', 'field': 'service'},
                {'name': 'datetime', 'label': 'Date & Time', 'field': 'datetime'},
                {'name': 'actions', 'label': 'Actions', 'field': 'actions'}
            ]
            # use defined columns type, starts with an empty table, key column is ID
            self.appointments_table = ui.table(columns=columns, rows=[], row_key='id')
            # update table
            self.refresh_appointments_table()

    def add_appointment(self) -> None:
        try:
            client_id = self.appointment_client.value # id of client
            service_id = self.appointment_service.value # id of service
            date_str = self.appointment_date.value # date of appointment
            time_str = self.appointment_time.value # time of appointment
            # valitity of given data
            if not client_id or not service_id or not date_str or not time_str:
                ui.notify("All fields are required", type='negative')
                return
            
            try:
                # str -> date/time format
                date_d = datetime.strptime(date_str, '%Y-%m-%d').date()
                time_t = datetime.strptime(time_str, '%H:%M').time()
            except ValueError as e:
                # validity if format isn't right
                ui.notify(f"Invalid date or time format: {str(e)}", type='negative')
                return
            # date + time
            dt = datetime.combine(date_d, time_t)
            # check availability of time with method from database.py
            if not self.db._is_time_slot_available(dt, service_id):
                ui.notify("Time slot not available", type='negative')
                return
            
            # add appointment with given data and with method from database.py
            appointment_id, _ = self.db.add_appointment(
                client_id=client_id,
                service_id=service_id,
                datetime_str=dt.isoformat(),
                status="planned"
            )
            # notification of success
            #ui.notify(f"Appointment #{appointment_id} booked", type='positive')
            # update table
            #self.refresh_appointments_table()
            if appointment_id:
                # notification of success
                ui.notify(f"Appointment #{appointment_id} booked", type='positive')
                # update table
                self.refresh_appointments_table()
            else:
                # notification of fail
                ui.notify(message, type='negative')
        except sqlite3.Error as e:
            # notification of fail
            ui.notify(f"Database error: {str(e)}", type='negative')
        except Exception as e:
            # notification of fail
            ui.notify(f"Error: {str(e)}", type='negative')

    def refresh_appointments_table(self) -> None:
        # list of all appointments
        appointments = self.db.get_all_appointments()
        rows = []
        # create rows of appointments
        for app in appointments:
            client = self.db.get_client_by_id(app.client_id)
            service = self.db.get_service_by_id(app.service_id)
            app_dt = datetime.fromisoformat(app.datetime)
            
            rows.append({
                'id': app.id,
                'client': client.name if client else "Unknown",
                'service': service.name if service else "Unknown",
                'datetime': app_dt.strftime('%Y-%m-%d %H:%M'),
                'actions': None  
            })
        # update rows in table
        self.appointments_table.rows = rows
        # save changes
        self.appointments_table.update()
        
        # add buttons with slots
        for row in self.appointments_table.rows:
            # dynamically inject content into table cells
            with self.appointments_table.add_slot('body-cell-actions', row['id']):
                # create new variable binding for each iteration
                with ui.row().classes('p-1 gap-1'):
                    # create delete button
                    ui.button(icon='delete', on_click=lambda _, id=row['id']: self.delete_entity('appointment', id)) \
                        .props('flat color=red')
    
    def delete_entity(self, entity_type: str, entity_id: int) -> None:
        try:
            success = False
            # if client was deleted
            if entity_type == 'client':
                success = self.db.delete_client(entity_id)
                if success:
                    ui.notify("Client deleted", type='positive')
            # if service was deleted
            elif entity_type == 'service':
                success = self.db.delete_service(entity_id)
                if success:
                    ui.notify("Service deleted", type='positive')
            # if appointment was deleted
            elif entity_type == 'appointment':
                success = self.db.delete_appointment(entity_id)
                if success:
                    ui.notify("Appointment deleted", type='positive')
            
            if success:
                # update data (where were deleted)
                if entity_type == 'client':
                    self.refresh_clients_table()
                    self._update_appointment_client_options()
                elif entity_type == 'service':
                    self.refresh_services_table()
                    self._update_appointment_service_options()
                elif entity_type == 'appointment':
                    self.refresh_appointments_table()  
                else:
                    # notification of fail
                    ui.notify(f"{entity_type.capitalize()} not found", type='warning')   
        except sqlite3.Error as e:
            # notification of fail
            ui.notify(f"Database error: {str(e)}", type='negative')
        except Exception as e:
            # notification of fail
            ui.notify(f"Error deleting {entity_type}: {str(e)}", type='negative')

# Run the app
if __name__ in {"__main__", "__mp_main__"}:
    app = ManagementApp()
    ui.run(title='Management', port=8080)