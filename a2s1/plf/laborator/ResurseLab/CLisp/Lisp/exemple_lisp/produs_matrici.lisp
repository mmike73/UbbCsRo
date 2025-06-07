
;; returneaza lista coloanelor matricii
(defun coloane (l)
    (cond
        ((null (car l)) nil)
        (t (cons (mapcar #'car l) (coloane (mapcar #'cdr l))))
    )
)

;; returneaza rezultatul inmultirii matricilor
(defun pr (l1 l2)
    (cond
        ((null (car l1)) nil)
        (t (cons (mapcar #'
            (lambda (l) 
                (apply #'+ (mapcar #'* (car l1) l))
            ) l2) (pr (cdr l1) l2)))
    )
)

(defun produs (l1 l2)
    (pr l1 (coloane l2))
)

;; 1 2  3 4  3 + 2 4 + 4   5 8
;; 3 4  1 2  9 + 4 12 + 8 13 20