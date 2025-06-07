(defun insert_dupa_poz_para (l e)
  (ins-helper l e 1))

(defun ins_helper (l e pozitie)
  (cond
    ((null l) nil)  
    ((and (> pozitie 1) (= 0 (mod pozitie 2))) 
        (cons 
            (car l)  ;; elementul curent
            e        ;; elementul de inserat
            (ins_helper (cdr l) e (+ 1 pozitie)) ;; restul
        )
    )
    (t  (cons 
            (car l) 
            (ins_helper (cdr l) e (+ 1 pozitie))
        )
    )
  )
) 

