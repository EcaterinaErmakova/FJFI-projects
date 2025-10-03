from dataclasses import dataclass
from datetime import datetime, time

# models.py (unchanged, already good)
from dataclasses import dataclass
from datetime import datetime, time

@dataclass
class Client:
    id: int
    name: str
    phone: str
    email: str = ""
    notes: str = ""
    
@dataclass
class Service:
    id: int
    name: str
    duration: int  # in minutes
    price: float

@dataclass
class Appointment:
    id: int
    client_id: int
    service_id: int
    datetime: datetime
    status: str  # planned/completed/canceled
