(defun num_ap_nelin (l e)
    (cond
        ((null l) 0)
        ((atom (car l))
            (cond
                ((= e (car l)) (+ 1 (num_ap_nelin (cdr l) e)))
                (t (num_ap_nelin (cdr l) e))
            )
        )
        (t (+ (num_ap_nelin (car l) e) (num_ap_nelin (cdr l) e)))
    )
)