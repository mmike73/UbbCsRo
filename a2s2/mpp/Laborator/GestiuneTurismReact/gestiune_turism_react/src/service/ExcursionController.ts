import { type Excursion } from "../types/Excursion";
import axios, { Axios, type AxiosInstance } from "axios"

export interface CrudController<T, ID = number> {
    getAll(): Promise<T[]>;

    get(id: ID): Promise<T>;

    create(entity: T): Promise<T>;

    update(entity: T): Promise<T>;

    delete(id: ID): Promise<T>;
}

export class ExcursionController implements CrudController<Excursion, number> {
    private baseUrl: string | undefined;
    private axios: AxiosInstance;
    private getToken: () => string | null;

    constructor(
        baseUrl: string | undefined, 
        axios: AxiosInstance,
        getToken: () => string | null
    ) {
        this.baseUrl = baseUrl;
        this.axios = axios;
        this.getToken = getToken;
    }

    private getAuthConfig() {
        const token = this.getToken();
        if (!token) {
            throw new Error("No authentication token available");
        }
        return {
            headers: {
                Authorization: `Bearer ${token}`
            }
        };
    }

    async getAll(): Promise<Excursion[]> {
        if (typeof(this.baseUrl) === "string") {
            const response = await this.axios.get<Excursion[]>(this.baseUrl, this.getAuthConfig());
            return response.data;
        }
        throw new Error("Invalid base URL");
    }

    async get(id: number): Promise<Excursion> {
        if (typeof(this.baseUrl) === "string") {
            const response = await this.axios.get<Excursion>(`${this.baseUrl}/${id}`, this.getAuthConfig());
            return response.data;
        }
        throw new Error("Invalid base URL");
    }

    async create(entity: Excursion): Promise<Excursion> {
        if (typeof(this.baseUrl) === "string") {
        const response = await this.axios.post<Excursion>(this.baseUrl, entity, this.getAuthConfig());
        return response.data
        }
        throw new Error("Invalid base URL");
    }

    async update(entity: Excursion): Promise<Excursion> {
        if (typeof(this.baseUrl) === "string") {
        const response = await this.axios.put<Excursion>(this.baseUrl, entity, this.getAuthConfig());
        return response.data;
        }
        throw new Error("Invalid base URL");
    }

    async delete(id: number): Promise<Excursion> {
        if (typeof(this.baseUrl) === "string") {
        const response = await this.axios.delete<Excursion>(`${this.baseUrl}/${id}`, this.getAuthConfig());
        return response.data;
        }
        throw new Error("Invalid base URL");
    }
}