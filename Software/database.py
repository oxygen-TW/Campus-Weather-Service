# -*- coding: utf-8 -*-
# /usr/bin/python3
import pymysql
import os


class Database:
    def __enter__(self):
        self.conn = pymysql.connect(host='DB_HOST',
                                    db='DB_NAME',
                                    port=3306, user='DB_USER',
                                    passwd='DB_PASSWORD',
                                    use_unicode=True,
                                    charset="utf8")

        self.cur = self.conn.cursor()
        return self.cur

    def __exit__(self, ex_type, ex_value, ex_tb):
        self.conn.commit()
        self.conn.close()


def query_fetchone(sql, data=None):
    with Database() as db:
        if data:
            db.execute(sql, data)
        else:
            db.execute(sql)
        return db.fetchone()


def query_fetchall(sql, data=None):
    with Database() as db:
        if data:
            db.execute(sql, data)
        else:
            db.execute(sql)
        return db.fetchall()


def insert_weather(data):
    with Database() as db:
        sql = """INSERT INTO weather_weather (time,temperature,humidity,uv,light,rainfall) VALUES (%s,%s,%s,%s,%s,%s)""".format(
            data[0], data[1], data[2], data[3], data[4], data[5])
        db.execute(sql, data)


#insert_weather(("2016/08/31 8:49:54", 1, 2, 3, 4, 5))
'''
create table weather ( time TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
                id int NOT NULL  ,
                temperature float(3,1),
                humidity float(3,1),
                uv tinyint(2),
                lignt int(5),
                pm float(2,1));
INSERT INTO weather (time,id,temperatur,humidity,uv,lignt,pm) value('2017/08/29 20:50:40',1,25,77,0,3,2.5);
'''