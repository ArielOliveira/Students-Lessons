package com.arielado;

import com.arielado.renderEngine.DisplayManager;
import com.arielado.renderEngine.Loader;
import com.arielado.renderEngine.MasterRenderer;
import com.arielado.renderEngine.OBJLoader;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import javax.vecmath.Quat4f;
import javax.vecmath.Vector3f;

import com.arielado.entities.Camera;
import com.arielado.entities.Entity;
import com.arielado.entities.Light;
import com.arielado.models.RawModel;
import com.arielado.models.TexturedModel;
import com.arielado.terrains.Terrain;
import com.arielado.textures.ModelTexture;
import com.arielado.textures.TerrainTexture;
import com.arielado.textures.TerrainTexturePack;
import com.arielado.toolbox.Maths;

import org.lwjgl.opengl.Display;

/**
 * Hello world!
 *
 */
public class App 
{
    public static void main( String[] args )
    {
        DisplayManager.createDisplay();
        Loader loader = new Loader();

        float[] cube = {
            -1f,  1f, -1f, //back 
             1f,  1f, -1f,        
             1f, -1f, -1f,        
            -1f, -1f, -1f,        

             1f,  1f, -1f, //right
             1f,  1f,  1f,
             1f, -1f,  1f,
             1f, -1f, -1f,

            -1f,  1f,  1f, //front 
             1f,  1f,  1f,           
             1f, -1f,  1f,         
            -1f, -1f,  1f,   
            
          
            -1f,  1f, -1f, //left
            -1f,  1f,  1f,
            -1f, -1f,  1f,
            -1f, -1f, -1f,

            -1f,  1f,  1f, //top
             1f,  1f,  1f,
             1f,  1f, -1f,
            -1f,  1f, -1f,

            -1f, -1f,  1f, //bottom
             1f, -1f,  1f,
             1f, -1f, -1f,
            -1f, -1f, -1f
        };

        int[] cubeIndices = {
            0, 1, 2, //back
            2, 3, 0,

            4, 5, 6, //right
            6, 7, 4,

            8, 11, 10, //front
            10, 9, 8,

            14, 13, 12, //left
            12, 15, 14,

            19, 16, 17, //top
            17, 18, 19,

            22, 21, 20, //bottom
            20, 23, 22
        };

        float[] cubeTexture = {
            0, 0,
            1, 0,
            1, 1,
            0, 1,

            0, 0,
            1, 0,
            1, 1,
            0, 1,

            0, 0,
            1, 0,
            1, 1,
            0, 1,

            0, 0,
            1, 0,
            1, 1,
            0, 1,
            
            0, 0,
            1, 0,
            1, 1,
            0, 1,

            0, 0,
            1, 0,
            1, 1,
            0, 1
        };



        RawModel grassObj = OBJLoader.loadObjModel("grassModel", loader);
        ModelTexture grassTexture = new ModelTexture(loader.loadTexture("grassTexture"));
        grassTexture.setTransparency(true);
        grassTexture.setFakeLightining(true);
        TexturedModel grassModel = new TexturedModel(grassObj, grassTexture);


        Entity grass = new Entity(grassModel, new Vector3f(400, -2, 0), new Quat4f(0, 0, 0, 1), 1);

        ModelTexture terrainTexture = new ModelTexture(loader.loadTexture("grass"));
        //Terrain terrain = new Terrain(0, 0, loader, terrainTexture);
        
        //Terrain terrain = new Terrain(0, 0, loader, new ModelTexture(loader.loadTexture("grass")));
        //Terrain terrain2 = new Terrain(0, -1, loader, new ModelTexture(loader.loadTexture("grass")));
        
        Light light = new Light(null, new Vector3f(400, 8000, 0), new Quat4f(0, 0, 0, 1), 1,  new Vector3f(1, 1, 1));
        Camera camera = new Camera(new Vector3f(-400, 0, 0), Maths.getRotation(new Vector3f(0, 1, 0), 45), .2f, .01f);

        RawModel treeObj = OBJLoader.loadObjModel("tree", loader);
        ModelTexture treeTexture = new ModelTexture(loader.loadTexture("tree"));
        TexturedModel treeModel = new TexturedModel(treeObj, treeTexture);

        List<Entity> trees = new ArrayList<>();
        Random random = new Random();
        int treeCount = random.nextInt(800);
        float x, z;
        for (int i = 0; i < treeCount; i++) {   
            x = random.nextFloat() * 800;
            if (random.nextInt(8) > 4 )
                z = random.nextFloat() * 800;
            else 
                z = random.nextFloat() * -800;

            Vector3f position = new Vector3f(x, -2, z);
            trees.add(new Entity(treeModel, position, new Quat4f(0, 0, 0, 1), 1));
        }
        
        MasterRenderer renderer = new MasterRenderer();
        
        renderer.processEntity(grass);
        //renderer.processTerrain(terrain);
       // renderer.processTerrain(terrain);
       // renderer.processTerrain(terrain2);
        for (Entity tree : trees)
            renderer.processEntity(tree);
        
        while(!Display.isCloseRequested()) {
            //entity.increasePosition(.025f, 0, 0);
            //entity.increaseRotation(new Vector3f(0, 1, 0), 0.0025f);
            
            renderer.render(light, camera);
           // light.increaseRotation(new Vector3f(0, 1, 0), 0.025f);
           // Vector3f targetPosition = Maths.QuaternionToVector(light.getRotation(), lightOffset);
          //  light.increasePosition(targetPosition.x, targetPosition.y, targetPosition.z);

            camera.move();
            
            DisplayManager.updateDisplay();
        }
        renderer.cleanUp();
        loader.cleanUp();
        DisplayManager.closeDisplay();
    }
}
