package com.arielado.toolbox;

import javax.vecmath.Matrix4f;
import javax.vecmath.Quat4f;
import javax.vecmath.Vector3f;

import com.arielado.entities.Camera;

public class Maths {
    public static Matrix4f createTransformationMatrix(Vector3f translation, Quat4f rotation, float scale) {
        Matrix4f matrix = new Matrix4f();
        
        matrix.setIdentity();
        matrix.setScale(scale);
        matrix.setRotation(rotation);
        matrix.setTranslation(translation);

        return matrix;
    }

    public static Matrix4f createViewMatrixRotation(Camera camera) {
        Matrix4f matrix = new Matrix4f();
        
        matrix.setIdentity(); 
        matrix.setRotation(camera.getRotation());

        return matrix;
    }

    public static Matrix4f createViewMatrixTranslation(Camera camera) {
        Matrix4f matrix = new Matrix4f();
        
        Vector3f cameraPos = camera.getPosition();
        Vector3f negativeCameraPos = new Vector3f(-cameraPos.x, -cameraPos.y, -cameraPos.z);
    
        matrix.setIdentity();
        matrix.setTranslation(cameraPos);      

        return matrix;
    }

    public static Quat4f getRotation(Vector3f dir, float angle) {
        Quat4f rotation = new Quat4f((float)Math.sin(angle/2)*dir.x,
                                        (float)Math.sin(angle/2)*dir.y,
                                        (float)Math.sin(angle/2)*dir.z,
                                        (float)Math.cos(angle/2));
        
        return rotation;
    }

    public static Vector3f QuaternionToVector(Quat4f quat, Vector3f vec){
        float num = quat.x * 2f;
        float num2 = quat.y * 2f;
        float num3 = quat.z * 2f;
        float num4 = quat.x * num;
        float num5 = quat.y * num2;
        float num6 = quat.z * num3;
        float num7 = quat.x * num2;
        float num8 = quat.x * num3;
        float num9 = quat.y * num3;
        float num10 = quat.w * num;
        float num11 = quat.w * num2;
        float num12 = quat.w * num3;
        Vector3f result = new Vector3f();
        result.x = (1f - (num5 + num6)) * vec.x + (num7 - num12) * vec.y + (num8 + num11) * vec.z;
        result.y = (num7 + num12) * vec.x + (1f - (num4 + num6)) * vec.y + (num9 - num10) * vec.z;
        result.z = (num8 - num11) * vec.x + (num9 + num10) * vec.y + (1f - (num4 + num5)) * vec.z;
        return result;
    }
}
