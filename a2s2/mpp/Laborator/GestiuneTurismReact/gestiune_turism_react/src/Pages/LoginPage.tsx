import React, { useState } from 'react';
import { useNavigate } from 'react-router-dom';
import useAuth from '../hooks/UseAuth';
import { type AuthState } from '../types/AuthState';
import axiosPublic from '../api/AxiosPublic';

export default function LoginPage() {
  const { login } = useAuth();
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  const [error, setError] = useState<string | null>(null);
  const navigate = useNavigate();

  const loginUser = async (e: React.FormEvent) => {
    e.preventDefault();
    setError(null);

    try {
      const response = await axiosPublic.post('/auth/login', {
        username, 
        password,
      });

      const data = response.data;
      const authState: AuthState = {
        user: data.user,
        token: data.token,
        expiresAt: data.expiresAt
      };

      login(authState);
      
    } catch (err: any) {
      const message = err.response?.data?.message || 'Login failed. Please try again later.';
      setError(message);
    }
  };

  return (
    <>
      <h1>Login</h1>
      <form onSubmit={loginUser}>
        <div>
          <label>Username:</label>
          <input
            type="text"
            value={username}
            onChange={(e) => setUsername(e.target.value)}
            required
          />
        </div>

        <div>
          <label>Password:</label>
          <input
            type="password"
            value={password}
            onChange={(e) => setPassword(e.target.value)}
            required
          />
        </div>

        {error && <p style={{ color: 'red' }}>{error}</p>}

        <button type="submit">Login</button>
      </form>
    </>
  );
}
