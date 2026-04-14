SELECT c.nombre_completo as nombre, SUM(cu.id_cuenta) as totalcuentas, 
CASE 
    WHEN sum(cu.id_cuenta) > 3 THEN 'CLIENTE VIP'
    ELSE 'CLIENTE STANDAR'
END AS clienteVip
 FROM clientes c
JOIN cuentas cu ON c.id_cliente = cu.id_dueno
GROUP BY c.id_cliente 
HAVING SUM(cu.id_cuenta) > 1;