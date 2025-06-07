(defun filter_nums (l)
    (cond
        ((null l) nil)
        ((numberp l) (list l))
        ((atom l) nil)
        (t (apply #'append (mapcar #'filter_nums l)))
    )
)

(defun length_of_list (l)
    (cond
        ((null l) 0)
        ((atom l) 1)
        (t (apply #'+ (mapcar #'length_of_list l)))
    )
)

(defun si (l)
    (cond
        ((null l) t)    
        (t (and (car l) (si (cdr l))))
    )
)

(defun verif_num_zig_zag (l ind)
    (cond
        ((null l)  t)
        ((and 
            (= 1 (mod ind 2)) 
            (not (null (cdr l))) 
            (< (car l) (cadr l))
         ) (and t (verif_num_zig_zag (cdr l) (+ 1 ind))))
        ((and 
            (= 0 (mod ind 2)) 
            (not (null (cdr l))) 
            (> (car l) (cadr l))
        ) (and t (verif_num_zig_zag (cdr l) (+ 1 ind))))
        ((and (null (cdr l)) (= 1 (mod ind 2))) t)
        (t nil)
    )
)

(defun este_zig_zag (l)
    ((lambda (e)
        (= 1 (mod (length_of_list e) 2))
        (verif_num_zig_zag e 1)
    ) (filter_nums l))
)