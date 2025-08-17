
-- Test 1: Simple SELECT ALL
SELECT * FROM users;

-- Test 2: SELECT specific columns
SELECT name, email FROM users;

-- Test 3: SELECT with column aliases (AS keyword)
SELECT name AS full_name, email AS email_address FROM users;

-- Test 4: SELECT with column aliases (without AS)
SELECT name full_name, email email_address FROM users;

-- Test 5: SELECT DISTINCT
SELECT DISTINCT department FROM employees;

-- Test 6: SELECT ALL (explicit)
SELECT ALL name FROM users;

-- =======================================================
-- WHERE CLAUSE TESTS - COMPARISON OPERATORS
-- =======================================================

-- Test 7: Simple WHERE with equals
SELECT * FROM products WHERE price = 100;

-- Test 8: WHERE with string comparison
SELECT * FROM users WHERE name = 'John Doe';

-- Test 9: WHERE with less than
SELECT * FROM products WHERE price < 100;

-- Test 10: WHERE with greater than
SELECT * FROM products WHERE price > 50;

-- Test 11: WHERE with less than or equal
SELECT * FROM products WHERE price <= 100;

-- Test 12: WHERE with greater than or equal
SELECT * FROM products WHERE price >= 50;

-- Test 13: WHERE with not equal (!=)
SELECT * FROM products WHERE category != 'Books';

-- Test 14: WHERE with not equal (<>)
SELECT * FROM products WHERE category <> 'Books';

-- =======================================================
-- LOGICAL OPERATORS IN WHERE CLAUSE
-- =======================================================

-- Test 15: WHERE with AND
SELECT * FROM employees WHERE department = 'IT' AND salary > 50000;

-- Test 16: WHERE with OR (original failing query)
SELECT * FROM products WHERE category = 'Electronics' OR category = 'Computers';

-- Test 17: Complex WHERE with parentheses
SELECT * FROM employees WHERE (department = 'IT' OR department = 'HR') AND salary > 40000;

-- Test 18: WHERE with NOT
SELECT * FROM users WHERE NOT name = 'John Doe';

-- Test 19: Multiple AND conditions
SELECT * FROM products WHERE price > 50 AND price < 200 AND category = 'Electronics';

-- Test 20: Multiple OR conditions
SELECT * FROM products WHERE category = 'Books' OR category = 'Electronics' OR category = 'Clothing';

-- =======================================================
-- NULL HANDLING
-- =======================================================

-- Test 21: WHERE with IS NULL
SELECT * FROM users WHERE phone IS NULL;

-- Test 22: WHERE with IS NOT NULL
SELECT * FROM users WHERE phone IS NOT NULL;

-- =======================================================
-- LIKE PATTERN MATCHING
-- =======================================================

-- Test 23: LIKE with wildcard
SELECT * FROM users WHERE name LIKE 'John%';

-- Test 24: LIKE with underscore wildcard
SELECT * FROM products WHERE product_code LIKE 'A_123';

-- =======================================================
-- IN OPERATOR
-- =======================================================

-- Test 25: IN with list of values
SELECT * FROM products WHERE category IN ('Electronics', 'Books', 'Clothing');

-- Test 26: NOT IN with list of values
SELECT * FROM products WHERE category NOT IN ('Electronics', 'Books');

-- =======================================================
-- BETWEEN OPERATOR
-- =======================================================

-- Test 27: BETWEEN with numbers
SELECT * FROM employees WHERE salary BETWEEN 30000 AND 80000;

-- Test 28: NOT BETWEEN
SELECT * FROM employees WHERE salary NOT BETWEEN 30000 AND 50000;

-- =======================================================
-- JOIN OPERATIONS
-- =======================================================

-- Test 29: Simple INNER JOIN
SELECT u.name, o.order_date FROM users u JOIN orders o ON u.id = o.user_id;

-- Test 30: INNER JOIN (explicit)
SELECT u.name, o.order_date FROM users u INNER JOIN orders o ON u.id = o.user_id;

-- Test 31: LEFT JOIN
SELECT u.name, o.order_date FROM users u LEFT JOIN orders o ON u.id = o.user_id;

-- Test 32: LEFT OUTER JOIN
SELECT u.name, o.order_date FROM users u LEFT OUTER JOIN orders o ON u.id = o.user_id;

-- Test 33: RIGHT JOIN
SELECT u.name, o.order_date FROM users u RIGHT JOIN orders o ON u.id = o.user_id;

-- Test 34: RIGHT OUTER JOIN
SELECT u.name, o.order_date FROM users u RIGHT OUTER JOIN orders o ON u.id = o.user_id;

-- Test 35: FULL OUTER JOIN
SELECT u.name, o.order_date FROM users u FULL OUTER JOIN orders o ON u.id = o.user_id;

-- Test 36: CROSS JOIN
SELECT u.name, p.product_name FROM users u CROSS JOIN products p;

-- Test 37: Multiple JOINs
SELECT u.name, o.order_date, p.product_name 
FROM users u 
JOIN orders o ON u.id = o.user_id 
JOIN products p ON o.product_id = p.id;

-- Test 38: JOIN with USING
SELECT u.name, o.order_date FROM users u JOIN orders o USING (user_id);

-- =======================================================
-- ARITHMETIC EXPRESSIONS
-- =======================================================

-- Test 39: SELECT with addition
SELECT product_name, price, price + 10 AS increased_price FROM products;

-- Test 40: SELECT with subtraction
SELECT product_name, price, price - 5 AS decreased_price FROM products;

-- Test 41: SELECT with multiplication
SELECT product_name, price, price * 1.1 AS price_with_tax FROM products;

-- Test 42: SELECT with division
SELECT product_name, price, price / 2 AS half_price FROM products;

-- Test 43: Complex arithmetic expression
SELECT product_name, price, (price * 1.1) + 5 AS final_price FROM products;

-- =======================================================
-- AGGREGATE FUNCTIONS
-- =======================================================

-- Test 44: COUNT function
SELECT COUNT(*) FROM users;

-- Test 45: COUNT with column
SELECT COUNT(email) FROM users;

-- Test 46: COUNT DISTINCT
SELECT COUNT(DISTINCT department) FROM employees;

-- Test 47: SUM function
SELECT SUM(salary) FROM employees;

-- Test 48: AVG function
SELECT AVG(price) FROM products;

-- Test 49: MIN function
SELECT MIN(price) FROM products;

-- Test 50: MAX function
SELECT MAX(salary) FROM employees;

-- =======================================================
-- GROUP BY AND HAVING
-- =======================================================

-- Test 51: Simple GROUP BY
SELECT department, COUNT(*) FROM employees GROUP BY department;

-- Test 52: GROUP BY with multiple columns
SELECT department, job_title, AVG(salary) FROM employees GROUP BY department, job_title;

-- Test 53: GROUP BY with HAVING
SELECT department, COUNT(*) FROM employees GROUP BY department HAVING COUNT(*) > 5;

-- Test 54: GROUP BY with WHERE and HAVING
SELECT department, AVG(salary) FROM employees WHERE salary > 30000 GROUP BY department HAVING AVG(salary) > 50000;

-- =======================================================
-- ORDER BY
-- =======================================================

-- Test 55: ORDER BY ASC (explicit)
SELECT * FROM products ORDER BY price ASC;

-- Test 56: ORDER BY DESC
SELECT * FROM products ORDER BY price DESC;

-- Test 57: ORDER BY default (should be ASC)
SELECT * FROM employees ORDER BY name;

-- Test 58: ORDER BY multiple columns
SELECT * FROM employees ORDER BY department ASC, salary DESC;

-- =======================================================
-- LIMIT AND OFFSET
-- =======================================================

-- Test 59: LIMIT only
SELECT * FROM products LIMIT 10;

-- Test 60: LIMIT with OFFSET
SELECT * FROM products LIMIT 10 OFFSET 20;

-- Test 61: OFFSET only
SELECT * FROM products OFFSET 5;

-- =======================================================
-- SUBQUERIES
-- =======================================================

-- Test 62: Subquery with EXISTS
SELECT * FROM users WHERE EXISTS (SELECT 1 FROM orders WHERE orders.user_id = users.id);

-- Test 63: Subquery with NOT EXISTS
SELECT * FROM users WHERE NOT EXISTS (SELECT 1 FROM orders WHERE orders.user_id = users.id);

-- Test 64: Subquery in IN clause
SELECT * FROM products WHERE category_id IN (SELECT id FROM categories WHERE name = 'Electronics');

-- =======================================================
-- CASE EXPRESSIONS
-- =======================================================

-- Test 65: Simple CASE expression
SELECT name, 
       CASE department 
           WHEN 'IT' THEN 'Technology'
           WHEN 'HR' THEN 'Human Resources'
           ELSE 'Other'
       END AS dept_full_name
FROM employees;

-- Test 66: Searched CASE expression
SELECT name,
       CASE 
           WHEN salary > 80000 THEN 'High'
           WHEN salary > 50000 THEN 'Medium'
           ELSE 'Low'
       END AS salary_range
FROM employees;

-- =======================================================
-- INSERT STATEMENTS
-- =======================================================

-- Test 67: Simple INSERT
INSERT INTO users (name, email) VALUES ('John Doe', 'john@example.com');

-- Test 68: INSERT multiple rows
INSERT INTO users (name, email) VALUES 
    ('Jane Smith', 'jane@example.com'),
    ('Bob Johnson', 'bob@example.com');

-- Test 69: INSERT all columns
INSERT INTO users VALUES (1, 'Alice Brown', 'alice@example.com', '555-1234');

-- Test 70: INSERT without column list
INSERT INTO categories VALUES ('Electronics');

-- =======================================================
-- UPDATE STATEMENTS
-- =======================================================

-- Test 71: Simple UPDATE
UPDATE users SET email = 'newemail@example.com' WHERE id = 1;

-- Test 72: UPDATE multiple columns
UPDATE employees SET salary = 55000, department = 'IT' WHERE id = 1;

-- Test 73: UPDATE with complex WHERE
UPDATE products SET price = price * 1.1 WHERE category = 'Electronics' AND price > 100;

-- Test 74: UPDATE without WHERE (affects all rows)
UPDATE products SET updated_date = '2024-01-01';

-- =======================================================
-- DELETE STATEMENTS
-- =======================================================

-- Test 75: Simple DELETE
DELETE FROM users WHERE id = 1;

-- Test 76: DELETE with complex WHERE
DELETE FROM orders WHERE order_date < '2023-01-01' AND status = 'cancelled';

-- Test 77: DELETE all rows (no WHERE clause)
DELETE FROM temp_table;

-- =======================================================
-- CREATE TABLE STATEMENTS
-- =======================================================

-- Test 78: Simple CREATE TABLE
CREATE TABLE test_table (id INT, name VARCHAR);

-- Test 79: CREATE TABLE with constraints
CREATE TABLE users_new (
    id INT PRIMARY KEY,
    name VARCHAR NOT NULL,
    email VARCHAR UNIQUE,
    age INT DEFAULT 18,
    phone VARCHAR
);

-- Test 80: CREATE TABLE with foreign key
CREATE TABLE orders_new (
    id INT PRIMARY KEY,
    user_id INT REFERENCES users(id),
    total DECIMAL,
    order_date DATE
);

-- =======================================================
-- DROP STATEMENTS
-- =======================================================

-- Test 81: DROP TABLE
DROP TABLE test_table;

-- Test 82: DROP DATABASE
DROP DATABASE test_db;

-- Test 83: DROP INDEX
DROP INDEX idx_user_email;

-- Test 84: DROP VIEW
DROP VIEW user_summary;

-- =======================================================
-- CREATE OTHER OBJECTS
-- =======================================================

-- Test 85: CREATE DATABASE
CREATE DATABASE new_database;

-- Test 86: CREATE INDEX
CREATE INDEX idx_product_name ON products (name);

-- Test 87: CREATE UNIQUE INDEX
CREATE UNIQUE INDEX idx_user_email ON users (email);

-- Test 88: CREATE VIEW
CREATE VIEW active_users AS SELECT * FROM users WHERE status = 'active';

-- =======================================================
-- ALTER TABLE STATEMENTS
-- =======================================================

-- Test 89: ALTER TABLE ADD COLUMN
ALTER TABLE users ADD phone VARCHAR;

-- Test 90: ALTER TABLE DROP COLUMN
ALTER TABLE users DROP email;

-- Test 91: ALTER TABLE MODIFY COLUMN
ALTER TABLE users MODIFY name VARCHAR NOT NULL;

-- Test 92: ALTER TABLE ADD PRIMARY KEY
ALTER TABLE users ADD PRIMARY KEY (id);

-- Test 93: ALTER TABLE DROP PRIMARY KEY
ALTER TABLE users DROP PRIMARY KEY;

-- Test 94: COMPLEX QUERY
SELECT DISTINCT u.name, u.email, COUNT(o.id) AS order_count, AVG(o.total) AS avg_order
FROM users u
LEFT JOIN orders o ON u.id = o.user_id
WHERE u.status = 'active' AND u.created_date > '2023-01-01'
GROUP BY u.id, u.name, u.email
HAVING COUNT(o.id) > 2
ORDER BY avg_order DESC, u.name ASC
LIMIT 50 OFFSET 10;

--EOF--