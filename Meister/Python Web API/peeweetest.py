from peewee import *
from playhouse.sqlite_ext import SqliteExtDatabase
import datetime

db = SqliteExtDatabase('my_database.db')

class BaseModel(Model):
	class Meta:
		database = db

class User(BaseModel):
	username = CharField(unique=True)

class Tweet(BaseModel):
	user = ForeignKeyField(User,related_name='tweets')
	message = TextField()
	created_date = DateTimeField(default=datetime.datetime.now
	is_pobulished = BooleanField(default=True)
