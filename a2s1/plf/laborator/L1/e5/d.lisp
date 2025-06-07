;;;; Definiti o functie care intoarce cel mai mare divizor comun al numerelor
;;;  dintr-o lista liniara.
(defun cmmdc (a b)
    (cond
        ((and (= a 0) (= b 0)) 1)
        ((= a 0) b)
        ((= b 0) a)
        ((< a b) (cmmdc a (mod b a)))
        (t (cmmdc b (mod a b)))
    )
) 

(defun cmmdc_lista (l)
    (cond
        ((null l) 1)
        ((numberp (car l)) (cmmdc (car l) (cmmdc_lista (cdr l))))
        (t (cmmdc_lista (cdr l)))
    )
)