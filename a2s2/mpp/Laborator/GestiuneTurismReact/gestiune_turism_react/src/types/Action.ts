import { type AuthState } from "./AuthState"

export type Action = 
    { type: 'LOGIN'; payload: AuthState } |
    { type: 'LOGOUT' } |
    { type: 'UPDATE_USER'; payload: AuthState };
