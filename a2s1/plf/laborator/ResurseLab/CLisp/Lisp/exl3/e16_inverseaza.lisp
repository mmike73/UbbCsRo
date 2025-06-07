(defun inverseaza (l Col)
    (cond
        ((null l) Col)
        (t (inverseaza (cdr l) (cons (car l) Col)))
    )
)

(defun inverseaza_dpt (l)
  (cond
    ((atom l) l) ; Dacă e atom, îl returnăm
    (t (apply #'(lambda (l) (inverseaza l nil)) (mapcar #'inverseaza_dpt l) nil)))) ; Inversăm recursiv sublistele

;; pentru fiecare lista pe care o intalnim, ii aplciam inverseaza
;; nu aplic direct in functie