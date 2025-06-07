import { createContext, useCallback, useReducer, useEffect, useState } from "react";
import { useNavigate } from 'react-router';
import type { AuthState } from "../types/AuthState";
import type { Action } from "../types/Action";

const initialState: AuthState = {
  user: null,
  token: '',
  expiresAt: '',
};

const AuthContext = createContext<{
    state: AuthState;
    login: (data: AuthState) => void;
    logout: () => void;
    updateUser: (data: AuthState) => void;
    loading: boolean;
}>({
    state: initialState,
    login: () => {},
    logout: () => {},
    updateUser: () => {},
    loading: true
});

const authReducer = (state: AuthState, action: Action): AuthState => {
  switch (action.type) {
    case 'LOGIN':
      return { ...state, ...action.payload };
    case 'LOGOUT':
      return { ...initialState };
    case 'UPDATE_USER':
      return { ...state, ...action.payload };
    default:
      return state;
  }
};

export const AuthProvider: React.FC<{ children: React.ReactNode }> = ({ children }) => {
  const [state, dispatch] = useReducer(authReducer, initialState);
  const navigate = useNavigate();

  const [loading, setLoading] = useState(true);

  const login = useCallback((data: AuthState) => {
    dispatch({ type: 'LOGIN', payload: data });
    localStorage.setItem('auth', JSON.stringify(data));
    navigate('/excursions');
  }, [navigate]);

  const logout = useCallback(() => {
    dispatch({ type: 'LOGOUT' });
    localStorage.removeItem('auth');
    navigate('/login');
  }, [navigate]);

  const updateUser = useCallback((data: AuthState) => {
    dispatch({ type: 'UPDATE_USER', payload: data });
    localStorage.setItem('auth', JSON.stringify({ ...state, ...data }));
  }, []);

  useEffect(() => {
    const storedAuth = localStorage.getItem('auth');
    if (storedAuth) {
      try {
        const parsed: AuthState = JSON.parse(storedAuth);
        if (parsed.token) {
          dispatch({ type: 'LOGIN', payload: parsed });
        }
      } catch (err) {
        console.error('Failed to parse stored auth', err);
      }
    }
    setLoading(false);
  }, []);

  return (
    <AuthContext.Provider value={{ state, login, logout, updateUser, loading }}>
      {children}
    </AuthContext.Provider>
  );
};

export default AuthContext;