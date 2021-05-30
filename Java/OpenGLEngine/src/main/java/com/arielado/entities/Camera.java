package com.arielado.entities;

import org.lwjgl.input.Keyboard;

import javax.vecmath.Quat4f;
import javax.vecmath.Vector3f;

import com.arielado.toolbox.Maths;

public class Camera {
    private float moveSpeed;
    private float rotationSpeed;
    private float speedBoost;
    private float rotationBoost;

    private Vector3f position;
    private Vector3f forward;
    private Vector3f up;
    private Vector3f right;
    private Quat4f rotation;

    public Camera() {
        moveSpeed = .25f;
        rotationSpeed = .5f;
        speedBoost = moveSpeed * 2;
        rotationBoost = rotationSpeed * 2;
        position = new Vector3f(0, 0 ,0);
        forward = new Vector3f(0, 0, 1);
        up = new Vector3f(0, 1, 0);
        right = new Vector3f(-1, 0, 0);
        rotation = new Quat4f(0, 0, 0, 1);
    }

    public Camera(Vector3f position, Quat4f rotation, float moveSpeed, float rotationSpeed) {
        this.moveSpeed = moveSpeed;
        this.rotationSpeed = rotationSpeed;
        this.speedBoost = moveSpeed * 2;
        this.rotationBoost = rotationSpeed * 2;
        this.position = position;
        this.rotation = rotation;
        
        forward = Maths.QuaternionToVector(rotation, new Vector3f(0, 0, 1));
        forward.x = -forward.x;

        up = Maths.QuaternionToVector(rotation, new Vector3f(0, 1, 0));
        up.x = -up.x;

        right = Maths.QuaternionToVector(rotation, new Vector3f(1, 0, 0));
        right.x = -right.x;
    }

    public void move() {
        if (Keyboard.isKeyDown(Keyboard.KEY_W)) 
            increasePosition(forward);

        if (Keyboard.isKeyDown(Keyboard.KEY_D))
            increasePosition(right);

        if (Keyboard.isKeyDown(Keyboard.KEY_A))
            increasePosition(new Vector3f(-right.x, -right.y, -right.z));

        if (Keyboard.isKeyDown(Keyboard.KEY_S))
            increasePosition(new Vector3f(-forward.x, -forward.y, -forward.z));

        if (Keyboard.isKeyDown(Keyboard.KEY_Q))
            increaseRotation(up, -rotationSpeed);

        if (Keyboard.isKeyDown(Keyboard.KEY_E)) 
            increaseRotation(up, rotationSpeed);

        if (Keyboard.isKeyDown(Keyboard.KEY_Z))
            increasePosition(new Vector3f(-up.x, -up.y, -up.z));

        if (Keyboard.isKeyDown(Keyboard.KEY_C))
            increasePosition(up);

        if (Keyboard.isKeyDown(Keyboard.KEY_LSHIFT)) {
            moveSpeed = speedBoost;
            rotationSpeed = rotationBoost;
        } else if (moveSpeed == speedBoost) {
            moveSpeed /= 2;
            rotationSpeed /= 2;
        }
        
        
    }
    public Vector3f getPosition() {
        return position;
    }

    public Quat4f getRotation() {
        return rotation;
    }

    private void increasePosition(Vector3f dir) {
        position.x += dir.x * moveSpeed;
        position.y += dir.y * moveSpeed;
        position.z += dir.z * moveSpeed;
    }

    public void increaseRotation(Vector3f dir, float angle) {
        rotation.mul(rotation, Maths.getRotation(dir, angle));

        forward = Maths.QuaternionToVector(rotation, new Vector3f(0, 0, 1));
        forward.x = -forward.x;

        up = Maths.QuaternionToVector(rotation, new Vector3f(0, 1, 0));
        up.x = -up.x;

        right = Maths.QuaternionToVector(rotation, new Vector3f(1, 0, 0));
        right.x = -right.x;
    }
}
