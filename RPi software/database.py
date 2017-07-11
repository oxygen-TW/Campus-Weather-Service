# -*- coding: utf-8 -*-
# /usr/bin/python3
import pymysql
import os

#usage: in the other file: database.insert_weather((datetime.now(),temperature, humidity, UV_value,light_value))
class Database:
    def __enter__(self):
        self.conn = pymysql.connect(host='203.72.63.200',
                                    port=3306, user='nhcc',
                                    passwd='nhcc9487',
                                    db = 'nhcciot',
                                    use_unicode=True,
                                    charset="utf8")
        self.cur = self.conn.cursor()
        return self.cur

    def __exit__(self, ex_type, ex_value, ex_tb):
        self.conn.commit()
        self.conn.close()

def query_fetchone(sql,data=None):
    with Database() as db:
        if data:
            db.execute(sql,data)
        else:
            db.execute(sql)
        return db.fetchone()
def query_fetchall(sql,data=None):
    with Database() as db:
        if data:
            db.execute(sql,data)
        else:
            db.execute(sql)
        return db.fetchall()

def insert_weather(data):
    #use_database(db)
    with Database() as db:
        if(data[0] > query_fetchone("""select time from weather;""")[0]):
            sql = """INSERT INTO weather (time,tpr,wet,uv,light) VALUES (%s,%s,%s,%s,%s)"""
