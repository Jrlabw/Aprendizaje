--1
SELECT c.customer_id, c.name, email FROM public.customers c
LEFT JOIN public.orders o ON c.customer_id = o.customer_id
WHERE o.customer_id IS NULL;

--2
SELECT COUNT(DISTINCT c.customer_id) as total_personas, c.country FROM public.customers c
JOIN public.orders o ON c.customer_id = o.customer_id
GROUP BY c.country
ORDER BY total_personas DESC;

--3 
SELECT p.product_name FROM products p
JOIN orderdetails od ON p.product_id = od.product_id
JOIN orders o ON od.order_id = o.order_id
GROUP BY p.product_id, p.product_name
HAVING sum(od.quantity_ordered) > 6500 AND MAX(o.order_date) <= '2023-09-10';
--4 
with comelon_customer AS (
    SELECT c.name, SUM(od.quantity_ordered) as total_ordenado
     FROM customers c
    JOIN orders o ON c.customer_id = o.customer_id
    JOIN orderdetails od ON o.order_id = od.order_id
    JOIN products p ON od.product_id = p.product_id
    WHERE p.product_name = 'Cornsilk Elite reinvent'
    GROUP BY c.customer_id
    ORDER BY total_ordenado DESC

)

SELECT name, total_ordenado FROM comelon_customer
LIMIT 1;

--5 
SELECT DATE_TRUNC('month', o.order_date) as mes, SUM(od.quantity_ordered) as total_ventas
FROM orders o
JOIN orderdetails od ON o.order_id = od.order_id
GROUP BY 1 --agrupar por la primera columna o podria ser DATE_TRUNC('month', o.order_date)
ORDER BY total_ventas DESC
LIMIT 1;

--6 
with total_sales as( 
    SELECT t.tag_name , SUM(od.quantity_ordered)as total FROM tags t
    JOIN customertags ct ON t.tag_id = ct.tag_id
    JOIN orders o ON ct.customer_id = o.customer_id
    JOIN orderdetails od ON o.order_id = od.order_id
    GROUP BY ct.tag_id, t.tag_name
    ORDER BY total DESC
) 

SELECT tag_name FROM total_sales
LIMIT 1;

--7

SELECT DISTINCT p.product_name FROM tags t
    JOIN customertags ct ON t.tag_id = ct.tag_id
    JOIN orders o ON ct.customer_id = o.customer_id
    JOIN orderdetails od ON o.order_id = od.order_id
    JOIN products p ON od.product_id = p.product_id
    WHERE t.tag_name IN ('Ashley', 'Karen')
    GROUP BY p.product_name
    HAVING COUNT (DISTINCT t.tag_name) = 2;

--8

SELECT DISTINCT p.product_name FROM tags t
    JOIN customertags ct ON t.tag_id = ct.tag_id
    JOIN orders o ON ct.customer_id = o.customer_id
    JOIN orderdetails od ON o.order_id = od.order_id
    JOIN products p ON od.product_id = p.product_id 
    WHERE tag_name = 'Ashley';