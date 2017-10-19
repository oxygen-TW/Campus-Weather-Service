# -*- coding: utf-8 -*-
# /usr/bin/python3
import pymysql
import os

# Important! Please change the configs below!

class Database:
    def __enter__(self):
        self.conn = pymysql.connect(host='HOST NAME',
                                    db='DB NAME',
                                    port=3306, user='User',
                                    passwd='PASSWORD',
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


def insert_data(data,TABLE_NAME):
    with Database() as db:
        sql = """INSERT INTO """ + TABLE_NAME + """(ValueI,ValueF) VALUES (%s,%s)""".format(data[0], data[1])
        db.execute(sql, data)


#insert_data((10,1.23),"TEST") For Test
