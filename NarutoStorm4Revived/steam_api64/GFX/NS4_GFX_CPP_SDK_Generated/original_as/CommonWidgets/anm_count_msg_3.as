package duel_boss4_fla
{
   import flash.display.MovieClip;
   import script.duel_boss4_lang.smb_count_msg1;
   import script.duel_boss4_lang.smb_count_msg2;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol1")]
   public dynamic class anm_count_msg_3 extends MovieClip
   {
      
      public var mc_msg_l:smb_count_msg2;
      
      public var mc_msg_r:smb_count_msg1;
      
      public function anm_count_msg_3()
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

