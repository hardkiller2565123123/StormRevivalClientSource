package script.duel_cutin2_lang
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol3")]
   public class nut_duel_link1 extends MovieClip
   {
      
      public function nut_duel_link1()
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

