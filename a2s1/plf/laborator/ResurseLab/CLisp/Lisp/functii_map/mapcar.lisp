;; functie MODIF care modifica o lista data ca parametru astfel:
;; atomii nenumerici raman nemodificati
;; atomii numerici isi dubleaza valoarea
;; modiicatile trebuiesc facute la toate nivelurile

;; (MODIF '(1 (b (4) c) (d (3 (5 f))))) -> (2 (b (8) c) (d (6 (10 f))))

(defun modif (l)
    (cond
        ((numberp l) (* 2 L))
        ((ATOM L) L)
        (t (mapcar #'modif L))    
    )
)


;; functie LGM - lungimea celei mai lungi subliste dintr-o
;; lista data L
;; daca sunt doar atomi - lista integrala

(defun LGM (l)
    (cond
        ((atom l) 0)
        (t (max (length l) (apply #'MAX (mapcar #'LGM L))))
    )
)