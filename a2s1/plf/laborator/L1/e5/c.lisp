;;;; Definiti o functie care determina suma a doua numere in reprezentare de
;;;  lista si calculeaza numarul zecimal corespunzator sumei.
(defun suma_helper (a b carry)
    (cond
        ((and (null a) (null b) (= carry 0)) '())
        ((and (null a) (null b)) (list carry))
        ((and (null a) (numberp (car b)))
            (cons (mod (+ (car b) carry) 10) (suma_helper nil (cdr b) (floor (+ (car b) carry) 10)))
        )
        ((and (null b) (numberp (car a)))
            (cons (mod (+ (car a) carry) 10) (suma_helper (cdr a) nil (floor (+ (car a) carry) 10)))
        )
        ((not (numberp (car b))) (suma_helper a (cdr b) carry))
        ((not (numberp (car a))) (suma_helper (cdr a) b carry))
        (t 
            (cons (mod (+ (car a) (car b) carry) 10) (suma_helper (cdr a) (cdr b) (floor (+ (car a) (car b) carry) 10)))
        )
    )
)

(defun my_append (l e)
    (cond
        ((null l) e)
        (t (cons (car l) (my_append (cdr l) e)))
    )
)

(defun oglinda (l)
    (cond
        ((null l) '())
        (t (my_append (oglinda (cdr l)) (list (car l))))
    )
)

(defun suma_lista (a b)
    (oglinda (suma_helper (oglinda a) (oglinda b) 0))
)

(defun transforma (r p)
    (cond
        ((null r) 0)
        (t (+ (* p (car r)) (transforma (cdr r) (* p 10))))
    )
)

(defun suma_dec (a b)
    (transforma (oglinda (suma_lista a b)) 1)
)
