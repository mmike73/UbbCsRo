;;;; Definiti o functie care interclaseaza cu pastrarea dublurilor doua liste
;;;  liniare sortate.
(defun interclas(a b)
    (cond 
        ((atom a) b)
        ((atom b) a)
        ((< (car a) (car b)) (cons (car a) (interclas (cdr a) b)))
        (t (cons (car b) (interclas a (cdr b))))
    )
)
