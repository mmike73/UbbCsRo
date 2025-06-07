(defun sau (l)
    (cond
        ((null l) nil)
        (t (or (car l) (sau (cdr l))))
    )
)

;; functioneaza si pentru subarbore
(defun apartine_arb (arb e)
    (cond
        ((equal arb e) t)
        ((atom arb) nil)
        (t (apply #'sau (list (mapcar #'(lambda (l) (apartine_arb l e)) arb))))
    )
)

;; daca avem nevoie deoar de atomi
(defun apartine_arb2 (arb e)
    (cond
        ((atom arb) (equal arb e))
        (t (apply #'sau (list (mapcar #'(lambda (l) (apartine_arb2 l e)) arb))))
    )
)
