import { useContext } from "react";
import { ExcursionServiceContext } from "../context/ExcursionServiceContext";  

export const useExcursionController = () => {
  const context = useContext(ExcursionServiceContext);
  if (!context) {
    throw new Error("useExcursionController must be used within an ExcursionProvider");
  }
  return context;
};
