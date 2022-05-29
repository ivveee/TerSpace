# Website Monitor System - WMS
WMS monitors the state of websites and logs it into a database. It is a homework for Aiven Backend developer position and an excercise of asyncio. The system consists of two parts:
- Producer - monitors websites listed in **websites.json** and sends the status packages to Kafka topic **website_check**
- Consumer - consumes packages and sends them to **results_log** table of **check_results** database
WMS relies on Aiven Kafka and Aiven PostrgeSQL. The following instruction will describe how to set everything up.

## Setting up Aiven services
To get things running you'll need:
- a running Aiven Kafka with **website_check** topic. Three partitions is recomended to feel the power of async. That could easily be done from a web interface.
- a running PostgreSQL database with the name **results_log**. We'll use a default ***avnadmin*** username. 
First to set up database
```
CREATE DATABASE check_results
    WITH 
    OWNER = avnadmin
    ENCODING = 'UTF8'
    LC_COLLATE = 'en_US.UTF-8'
    LC_CTYPE = 'en_US.UTF-8'
    TABLESPACE = pg_default
    CONNECTION LIMIT = -1;
```
And to create a table
```
CREATE TABLE IF NOT EXISTS public.results_log
(
    "timestamp" numeric NOT NULL,
    url text COLLATE pg_catalog."default" NOT NULL,
    result text COLLATE pg_catalog."default" NOT NULL,
    response_time real,
    regex_result boolean
)

TABLESPACE pg_default;

ALTER TABLE IF EXISTS public.results_log
    OWNER to avnadmin;
```
## Setting up Website Monitor System

