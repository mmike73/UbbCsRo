import React, { createContext, useContext } from "react";
import { ExcursionController } from "../service/ExcursionController";
import useAxiosPrivate from "../hooks/UseAxiosPrivate";

export const ExcursionServiceContext = createContext<ExcursionController | null>(null);

export const ExcursionServiceProvider: React.FC<{ children: React.ReactNode }> = ({ children }) => {
    const axiosPrivate = useAxiosPrivate();
    const controller = new ExcursionController(
        import.meta.env.VITE_API_URL, 
        axiosPrivate,     
        () => {
            const auth = localStorage.getItem('auth');
            return auth ? JSON.parse(auth).token : null;
    });

    return (
        <ExcursionServiceContext.Provider value={controller}>
            {children}
        </ExcursionServiceContext.Provider>
    );
};