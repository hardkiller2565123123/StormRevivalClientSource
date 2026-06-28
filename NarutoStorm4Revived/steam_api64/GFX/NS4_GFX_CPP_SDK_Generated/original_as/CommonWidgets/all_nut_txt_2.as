package script.msg_match_m_txt
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol36")]
   public class all_nut_txt extends MovieClip
   {
      
      public var mc_msg_match_num:nut_msg_match_num;
      
      public function all_nut_txt()
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

