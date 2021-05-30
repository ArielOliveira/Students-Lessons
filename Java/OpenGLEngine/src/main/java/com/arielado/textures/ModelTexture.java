package com.arielado.textures;

public class ModelTexture {
    private int textureID;

    private float shineDamper = 1;
    private float reflectivity = 0;
    
    private boolean transparency = false;
    private boolean fakeLightning = false;  

    public ModelTexture(int id) {
        this.textureID = id;
    }
    
    public int getID() {
        return this.textureID;
    }

    public void setTransparency(boolean value) {
        transparency = value;
    }

    public boolean hasTransparency() {
        return transparency;
    }

    public void setFakeLightining(boolean value) {
        fakeLightning = value;
    }

    public boolean useFakeLightining() {
        return fakeLightning;
    }

    public float getShineDamper() {
        return shineDamper;
    }

    public void setShineDamper(float shineDamper) {
        this.shineDamper = shineDamper;
    }

    public float getReflectivity() {
        return reflectivity;
    }

    public void setReflectivity(float reflectivity) {
        this.reflectivity = reflectivity;
    }
}
