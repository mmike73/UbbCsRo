import { useEffect, useState } from "react";
import { type Excursion } from "../types/Excursion";
import { useExcursionController } from "../hooks/UseExcursionController";
import  useAuth  from '../hooks/UseAuth';
import { useNavigate } from "react-router";

export default function ExcursionContainer() {
    const { state, logout } = useAuth();
    const navigate = useNavigate();

    useEffect(() => {
        const now = new Date().getTime();
        const expiresAt = new Date(state.expiresAt).getTime();
        console.log("Expites at " + expiresAt);
        console.log(state.token);
        console.log(now);
        console.log(expiresAt);
        console.log(state.token && now >= expiresAt);
        if (state.token && now >= expiresAt) {
            console.log("Token expired, logging out...");
            logout();
            navigate("/login");
        }
    }, [state.token, state.expiresAt, logout, navigate]);

    const excursionController = useExcursionController();
    const [excursionList, setExcursionList] = useState<Excursion[]>([]);
    const [editingId, setEditingId] = useState<number | null>(null);
    const [editData, setEditData] = useState<Partial<Excursion>>({});
    const [newExcursion, setNewExcursion] = useState<Partial<Excursion>>({
        id: -1,
        attraction: "",
        boardingDateTime: "",
        transportFirm: "",
        noSeats: 0,
        price: 0
    });
 
    useEffect(() => {
        const fetchExcursions = async () => {
            const excursions = await excursionController.getAll();
            setExcursionList(excursions);
        }
        fetchExcursions();
    }, []);

    const handleEditClick = (excursion: Excursion) => {
        setEditingId(excursion.id);
        setEditData({...excursion});
    };

    const handleCancelEdit = () => {
        setEditingId(null);
        setEditData({});
    };

    const handleSaveEdit = async (id: number) => {
        const fullExcursion: Excursion = {
            id,
            attraction: editData.attraction || "",
            boardingDateTime: editData.boardingDateTime || "",
            transportFirm: editData.transportFirm || "",
            noSeats: editData.noSeats ?? 0,
            price: editData.price ?? 0,
        };

        await excursionController.update(fullExcursion);
        const excursions = await excursionController.getAll();
        setExcursionList(excursions);  
        handleCancelEdit();
    }

    const handleDelete = async (id: number) => {
        await excursionController.delete(id);
        const excursions = await excursionController.getAll();
        setExcursionList(excursions);    
    }

    const handleAdd = async () => {
        const fullExcursion: Excursion = {
            id: -1,
            attraction: newExcursion.attraction || "",
            boardingDateTime: newExcursion.boardingDateTime || "",
            transportFirm: newExcursion.transportFirm || "",
            noSeats: newExcursion.noSeats ?? 0,
            price: newExcursion.price ?? 0,
        };
        await excursionController.create(fullExcursion);
        const excursions = await excursionController.getAll();
        setExcursionList(excursions);
        setNewExcursion({
            attraction: "",
            boardingDateTime: "",
            transportFirm: "",
            noSeats: 0,
            price: 0
        });
    };

    const handleEditFieldChange = (field: keyof Excursion, value: string | number) => {
        setEditData(prev => ({
            ...prev,
            [field]: value
        }));
    };

    const handleLogout = () => {
        logout();
    };

    return (
        <>
            <h1>Available excursions:</h1>
            <table>
                <thead>
                    <tr>
                        <th>Attraction</th>
                        <th>DepartureDateTime</th>
                        <th>TransportCompany</th>
                        <th>NoSeats</th>
                        <th>Price</th>
                        <th>Actions</th>
                    </tr>
                </thead>
                <tbody>
                    {excursionList.map((e) => (
                        editingId === e.id ? (
                            <tr key={e.id}>
                                <td>
                                    <input 
                                        value={editData.attraction || ""} 
                                        onChange={(e) => handleEditFieldChange('attraction', e.target.value)} 
                                    />
                                </td>
                                <td>
                                    <input 
                                        value={editData.boardingDateTime || ""} 
                                        onChange={(e) => handleEditFieldChange('boardingDateTime', e.target.value)} 
                                    />
                                </td>
                                <td>
                                    <input 
                                        value={editData.transportFirm || ""} 
                                        onChange={(e) => handleEditFieldChange('transportFirm', e.target.value)} 
                                    />
                                </td>
                                <td>
                                    <input 
                                        type="number" 
                                        value={editData.noSeats ?? 0} 
                                        onChange={(e) => handleEditFieldChange('noSeats', parseInt(e.target.value))} 
                                    />
                                </td>
                                <td>
                                    <input 
                                        type="number" 
                                        value={editData.price ?? 0} 
                                        onChange={(e) => handleEditFieldChange('price', parseFloat(e.target.value))} 
                                    />
                                </td>
                                <td>
                                    <button onClick={() => handleSaveEdit(e.id)}>Save</button>
                                    <button onClick={handleCancelEdit}>Cancel</button>
                                </td>
                            </tr>
                        ) : (
                            <tr key={e.id}>
                                <td>{e.attraction}</td>
                                <td>{e.boardingDateTime}</td>
                                <td>{e.transportFirm}</td>
                                <td>{e.noSeats}</td>
                                <td>{e.price}</td>
                                <td>
                                    <button 
                                        onClick={() => handleEditClick(e)} 
                                        disabled={editingId !== null && editingId !== e.id}
                                    >
                                        Edit
                                    </button>
                                    <button 
                                        onClick={() => handleDelete(e.id)} 
                                        disabled={editingId !== null}
                                    >
                                        Delete
                                    </button>
                                </td>
                            </tr>
                        )
                    ))}
                    <tr>
                        <td>
                            <input 
                                value={newExcursion.attraction || ""} 
                                onChange={e => setNewExcursion(data => ({ ...data, attraction: e.target.value }))} 
                            />
                        </td>
                        <td>
                            <input 
                                value={newExcursion.boardingDateTime || ""} 
                                onChange={e => setNewExcursion(data => ({ ...data, boardingDateTime: e.target.value }))} 
                            />
                        </td>
                        <td>
                            <input 
                                value={newExcursion.transportFirm || ""} 
                                onChange={e => setNewExcursion(data => ({ ...data, transportFirm: e.target.value }))} 
                            />
                        </td>
                        <td>
                            <input 
                                type="number" 
                                value={newExcursion.noSeats || 0} 
                                onChange={e => setNewExcursion(data => ({ ...data, noSeats: parseInt(e.target.value) }))} 
                            />
                        </td>
                        <td>
                            <input 
                                type="number" 
                                value={newExcursion.price || 0} 
                                onChange={e => setNewExcursion(data => ({ ...data, price: parseFloat(e.target.value) }))} 
                            />
                        </td>
                        <td>
                            <button onClick={handleAdd} disabled={editingId !== null}>Add</button>
                        </td>
                    </tr>
                </tbody>
            </table>
            <button onClick={ handleLogout }>
                Logout
            </button>
        </>
    );
}