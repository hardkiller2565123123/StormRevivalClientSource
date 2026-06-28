package script.duel_boss4_lang
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol6")]
   public class smb_count_msg1 extends MovieClip
   {
      
      public function smb_count_msg1()
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

