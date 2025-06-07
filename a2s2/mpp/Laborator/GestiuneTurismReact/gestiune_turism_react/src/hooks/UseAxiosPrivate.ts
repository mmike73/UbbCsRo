import { useEffect } from "react";
import axiosPrivate from "../api/AxiosPrivate";
import useAuth from "./UseAuth";

const useAxiosPrivate = () => {
    const { state, logout, updateUser } = useAuth();

    useEffect(() => {
        const requestIntercept = axiosPrivate.interceptors.request.use(
            config => {
                if (state.token) {
                    
                    const expiresAt = new Date(state.expiresAt).getTime();
                    console.log("Datetime of exporation: !!!!!!!!!!!!",expiresAt);
                    if (Date.now() >= expiresAt) {
                        logout();
                        return Promise.reject(new Error("Token expired!"));
                    }
                    config.headers['Authorization'] = `Bearer ${state.token}`;
                }
                return config;
            },
            error => Promise.reject(error)
        );

        return () => {
            axiosPrivate.interceptors.request.eject(requestIntercept);
        }
    }, [state.token, state.expiresAt, logout]);
    
    return axiosPrivate;
};

export default useAxiosPrivate;