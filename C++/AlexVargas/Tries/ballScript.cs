using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class BallForce : MonoBehaviour
{
    public Rigidbody ball;
    public float shotPower = 0f;
    public float rotateSpeed = 15f;
    private int counter = 0;
    public Transform Player;
    public Transform Flag;
    public float breakForce = 5f;
    public Vector3 direction;
    public Force shotPowerText;
    private bool add = false;
    public AudioSource win;
    public StrokeCounter strokeScript;
    public ForceCounter forceScript;

    public void LoadScene(string sceneName)
    {

        SceneManager.LoadScene(sceneName);
    }

    void OnCollisionEnter(Collision col)
    {
        
        if(col.gameObject.tag == "Wall")
        {
            
            ball.velocity =  ball.velocity + col.transform.forward;
        }
        if (col.gameObject.tag == "Flag")
        {
            win.Play();

            LoadScene("Level 2");

            
        }
    }

    // Update is called once per frame
    void Update()
    {

        Vector3 newDirection = (transform.position - Player.position).normalized;

       
            direction = newDirection;

        

        Debug.DrawLine(transform.position, direction, Color.blue, 100);
        transform.position = ball.position;
    
       
        if(Input.GetKey(KeyCode.Space))
        {
            
            shotPower += 1f;
            Debug.Log(shotPower);

            //      AddToForce();

            forceScript.AddToForce();
            add = true;
        }
        else
        {
              ball.AddForce(direction * shotPower);
           

            shotPower = 0f;
          
            strokeScript.AddToStroke();
            add = true;
          
            forceScript.ResetForce();

        }

    }
}
