(defun list_all_lists (l)
    (cond
        ((null l) nil)
        ((atom (car l)) (list_all_lists (cdr l)))
        (t (cons l (append (list_all_lists (car l)) (list_all_lists (cdr l)))))
    )
)

;; mai adauga lista propriu zisa separat
;; append la listel;e deja facute, cons mai pune paranteze - cons folosit doar pentru a adauga noi elemente