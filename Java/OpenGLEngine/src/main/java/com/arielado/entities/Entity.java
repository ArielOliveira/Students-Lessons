package com.arielado.entities;

import javax.vecmath.Quat4f;
import javax.vecmath.Vector3f;

import com.arielado.models.TexturedModel;
import com.arielado.toolbox.Maths;

public class Entity {
    private TexturedModel model;
    private Vector3f position;
    private Quat4f rotation;
    private float scale;

    public Entity(TexturedModel model, Vector3f position, Quat4f rotation, float scale) {
        this.model = model;
        this.position = position;
        this.rotation = rotation;
        this.scale = scale;
    }

    public void increasePosition(float dx, float dy, float dz) {
        this.position.x += dx;
        this.position.y += dy;
        this.position.z += dz;
    }

    public void increaseRotation(Vector3f dir, float angle) {
        rotation.mul(rotation, Maths.getRotation(dir, angle));
    }

    public Quat4f getRotation() {
        return rotation;
    }

    public TexturedModel getModel() {
        return model;
    }

    public void setModel(TexturedModel model) {
        this.model = model;
    }

    public Vector3f getPosition() {
        return position;
    }

    public void setPosition(Vector3f position) {
        this.position = position;
    }

    

    public float getScale() {
        return scale;
    }

    public void setScale(float scale) {
        this.scale = scale;
    }
}
