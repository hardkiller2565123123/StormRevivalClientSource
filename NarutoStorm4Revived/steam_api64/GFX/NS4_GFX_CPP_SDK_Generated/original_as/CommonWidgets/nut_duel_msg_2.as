package script.duel_cutin_lang
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol19")]
   public class nut_duel_msg extends MovieClip
   {
      
      public function nut_duel_msg()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
   }
}

