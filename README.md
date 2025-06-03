Примери
1) data/Catalog1.csv
Този файл показва добре как работят командите: print, showtables, describe, select, update, delete, insert, rename, aggregate, count.
За print и select да се използва Employees таблицата, за да се покаже извеждането по страници.
За count е добре да се използва Employees, за да се изведе число по-голямо от 1. 
2) data/ICatalog.csv
Има две таблици в този файл, които показват работата на innerjoin. Join-а става по нулевата колона.
3) import командата може да се демонстрира като се създаде нов файл и се добавят произволни таблици от data директорията.
4) export може да се демонстрира добре чрез data/Catalog1.csv. Може да се даде адреса на произволен файл(т.е. да се създаде нов файл, където да се запише информацията) или да се запише във data/EmptyFile.csv(той е вече създаден).
5) Тестването за поддържане на NULL стойности става най-добре като в произволен каталог се добавят(insert) редове с NULL стойности и се викат команди върху тези редове. В конзолата NULL се отбелязва като „“ или  (празно място).
6) addcolumn може да се тества със произволен каталог.
7) Командите свързани със работа с командния ред може да се демонстрират със всеки един от предоставените каталози.
Забележки: 
-Ако през конзолата се добавя нова String клетка съставена от няколко думи се използват кавички за въвеждане(т.е. „Better HR Personal”)
-Работи се със .csv файлове.
-Една таблица изглежда така:

Departments
Integer,String,String
DeptID,DeptName,Location
10,Engineering,Building A 
20,Marketing,Building B 
30,Sales,Building C 
40,Support,Building A 

- Един каталог изглежда така:

Employees,data/employees.csv
Departments,data/departments_new.csv
Projects,data/projects_new.csv
Investments,data/investments.csv
ProductsNew,data/products.csv

- Има много качени примерни файлове във директорията data

