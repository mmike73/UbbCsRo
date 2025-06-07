;;;; Definiti o functie care substituie un element E prin elementele unei liste
;;;  L1 la toate nivelurile unei liste date L.

;;; toate aparitiile elementului:
(defun substituie_toate (l e l1)
    (cond
        ((null l) ())
        ((equal e (car l)) (cons l1 (substituie_toate (cdr l) e l1)))
        ((listp (car l)) 
            (cons 
                (substituie_toate (car l) e l1) 
                (substituie_toate (cdr l) e l1)
            )
        )
        (t (cons (car l) (substituie_toate (cdr l) e l1)))
    )
)