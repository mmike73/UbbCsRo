import { useState } from 'react'
import ExcursionContainer from './components/ExcursionsContainer'
import { ExcursionServiceProvider } from './context/ExcursionServiceContext'
import { BrowserRouter as Router, Route, Routes, Navigate, BrowserRouter } from 'react-router-dom';
import { PrivateRoute } from './components/PrivateRoute';
import LoginPage from './Pages/LoginPage';
import { AuthProvider } from './context/AuthProvider';
import { PublicRoute } from './components/PublicRoute';

export default function App() {

  return (
    <BrowserRouter>
      <AuthProvider>
        <Routes>
          <Route 
            path="/"
            element={<Navigate to="/excursions" />}
          />
          <Route 
            path="/login" 
            element={
              <PublicRoute>
                <LoginPage />
              </PublicRoute>
            } 
          />
          <Route
            path="/excursions"
            element={
              <PrivateRoute>
                <ExcursionServiceProvider>
                  <ExcursionContainer />
                </ExcursionServiceProvider>
              </PrivateRoute>
            }
          />
        </Routes>
      </AuthProvider>
    </BrowserRouter>
  );
}
