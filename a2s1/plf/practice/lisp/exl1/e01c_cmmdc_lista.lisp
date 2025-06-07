(defun cmmdc (a b)
    (cond
        ((= 0 a) b)
        ((= 0 b) a)
        ((> a b) (cmmdc b (mod a b)))
        (t (cmmdc a (mod b a)))
    )
)

(defun cmmdc_lista (l)
    (cmmdc_lista_helper l 0)

(defun cmmdc_lista_helper (l crt)
    (cond
        ((null l) crt)
        ((numberp (car l)) (cmmdc_lista_helper (cdr l) (cmmdc (car l) crt)))
        ((listp (car l)) (cmmdc_lista_helper (cdr l) (cmmdc_lista_helper (car l) crt)))
        (t (cmmdc_lista_helper (cdr l) crt))
    )
)