import React from 'react';
import { Navigate } from 'react-router';
import useAuth from '../hooks/UseAuth';

export const PublicRoute: React.FC<{ children: React.ReactNode }> = ({ children }) => {
    const { state, loading } = useAuth();

    if (loading) {
        return <div>Loading ...</div>
    }

    return state.token? <Navigate to="/excursions" /> : children;
}