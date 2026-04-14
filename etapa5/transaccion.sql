SET statement_timeout = '10s';
ROLLBACK;
DO $$ 
DECLARE 
sender_id INTEGER;
sender_balance INTEGER;
id_recibe INTEGER;
monto INTEGER := 100;

BEGIN
SELECT ac.user_id, ac.balance
INTO sender_id, sender_balance
FROM public.account ac
JOIN public."user" u ON ac.user_id = u.id
WHERE u.email = 'bill.johnson@fmail.com'
FOR UPDATE;

IF NOT FOUND THEN 
    RAISE EXCEPTION 'TRANSACCION FALLIDA: USUARIO NO ENCONTRADO';
end IF;

IF sender_balance < monto THEN 
    RAISE EXCEPTION 'SALDO INSUFICIENTE';
END IF;

SELECT id INTO id_recibe
FROM "user" u
WHERE u.email = 'craig.williams@hmail.com';

IF NOT FOUND THEN
    RAISE EXCEPTION 'USUARIO NO ENCONTRADO';
END IF;


UPDATE account SET balance = balance - monto 
WHERE user_id = sender_id;
UPDATE account SET balance = balance + monto
WHERE user_id = id_recibe;
EXCEPTION
    WHEN query_canceled THEN
    RAISE WARNING 'TIEMPO DE ESPERA AGOTADO, SE HIZO ROLLBACK';
    WHEN OTHERS THEN
        RAISE NOTICE 'Ocurrió un error: % SE HIZO ROLLBACK', SQLERRM;

END $$;