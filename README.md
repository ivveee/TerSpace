# Website Monitor System - WMS
WMS monitors the state of websites and logs it into a database. It is a homework for Aiven Backend developer position and an excercise of asyncio. The system consists of two parts:
- Producer - monitors websites listed in `websites.json` asyncronosly and sends the status packages to Kafka topic `website_check`
- Consumer - asyncronosly consumes packages and sends them to `results_log` table of `check_results` database
WMS relies on Aiven Kafka and Aiven PostrgeSQL. The following instruction will describe how to set everything up.

## Setting up Aiven services
To get things running you'll need:
1. A running Aiven Kafka with `website_check` topic. Three partitions are recomended to feel the power of async. That could easily be done from the web interface.
2. A running PostgreSQL database with the name `results_log`. We'll use a default ***avnadmin*** username. 
First to set up database run 
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

Producer and Consumer run in separate environments and are built independently. This could be done on different environments. They use the same Kafka access keys, that are stored in `resources` folder as well as lists of websites to check and PostgreSQL username and passwords.
1. To build Producer and Consumer you'll need `Python 3.10` (there are some fancy type hinting features one cannot refuse to employ). Once you have cloned current repository to your local machine please install `Pipenv`
```
pip install --user pipenv
```
2. In `producer` and `consumer` folders run 
```
pipenv install
```
3. Download yur Kafka access keys (also - web interface) and put them into the directory `\resources\certificates`. Or you could use a directory of your choice and specify it in `\resources\kafka_certificates.json`.


- `service.key` - Access Key
- `service.cert` - Access Certificate
- `ca.pem` -  CA Certificate

And enter your Kafaka service uri in `\resources\kafka_certificates.json`

4. Enter your PostgreSQL credentials to  `\resources\db_access_data.json`
- `user` - PostgreSQL User name, by default avnadmin (if the SQL frome above is not modified - that's username you need)
- `password` - PostgreSQL password
- `host` - your Aiven PostgreSQL address (will look like ******.aivencloud.com",
- `port` - your Aiven PostgreSQL port. The default is `27160` but it is advised to check.

5. Look through website lists 
Websites to be checked are stored in `\resources\websites.json`
There is an example of a **very** diverse group of blocked sites that are monitored by Citizen Lab -  https://github.com/citizenlab/test-lists


You could set up your own group using syntax:

`[<url>,<regex>]` where `url` is an adress and `regex` is Python re regular expression rule to check on the site body. Currently it works only on the first 500 kb of the body. Or `[<url>]` if you don't need regex check

6. Run Consumer by running `pipenv run consumer.py`
7. Run Producer by running `pipenv run producer.py`
8. 
