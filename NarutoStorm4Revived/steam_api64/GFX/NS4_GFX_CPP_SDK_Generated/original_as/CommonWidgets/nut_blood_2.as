package eff_blood_fla
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol1")]
   public dynamic class nut_blood_2 extends MovieClip
   {
      
      public function nut_blood_2()
      {
         super();
         addFrameScript(10,this.frame11,20,this.frame21);
      }
      
      internal function frame11() : *
      {
         this.stop();
      }
      
      internal function frame21() : *
      {
         this.stop();
      }
   }
}

