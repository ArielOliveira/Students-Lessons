package com.arielado.entities;

import javax.vecmath.Quat4f;
import javax.vecmath.Vector3f;

import com.arielado.models.TexturedModel;

public class Light extends Entity {
    private Vector3f color;

    public Light(TexturedModel model, Vector3f position, Quat4f rotation, float scale, Vector3f color) {
        super(model, position, rotation, scale);
        this.color = color;
    }

    public Vector3f getColor() {
        return color;
    }

    public void setColor(Vector3f color) {
        this.color = color;
    }
}
