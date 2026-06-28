package script.duel_boss
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol1")]
   public class anm_up_ok extends MovieClip
   {
      
      public function anm_up_ok()
      {
         super();
         addFrameScript(5,this.frame6);
      }
      
      internal function frame6() : *
      {
         this.stop();
      }
   }
}

