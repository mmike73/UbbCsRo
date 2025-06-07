(defun is_part (e l)
    (cond
        ((null l) nil)
        ((= (car l) e) t)
        (t (is_part e (cdr l)))
    )
)

(defun is_part_depth (e l)
    (cond
        ((null l) nil)
        ((and (atom (car l)) (= (car l) e)) t)
        ((atom (car l)) (is_part_depth e (cdr l)))
        (t (or (is_part_depth e (cdr l)) (is_part_depth e (car l))))
    )
)

(defun list_to_set (l)
    (list_to_set_aux l ())
)

(defun list_to_set_aux (l Col)
    (cond
        ((null l) Col)
        ((and (atom (car l)) (not (is_part (car l) Col))) (list_to_set_aux (cdr l) (append Col (list (car l)))))
        (t (list_to_set_aux (cdr l) Col))
    )
)