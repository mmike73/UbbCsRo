(defun atoms_mirrored (l)
    (cond
        ((null l) nil)
        ((atom (car l)) (append (atoms_mirrored (cdr l)) (list (car l))))
        (t (append (atoms_mirrored (cdr l)) (atoms_mirrored (car l))))
    )
)

(defun atoms_same_order (l)
    (cond
        ((null l) nil)
        ((atom (car l)) (cons (car l) (atoms_same_order (cdr l))))
        (t (append (atoms_same_order (car l)) (atoms_same_order (cdr l))))
    )
)

