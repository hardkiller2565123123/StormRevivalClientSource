package duel_act_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol20")]
   public dynamic class anm_fin_txt_2p_16 extends MovieClip
   {
      
      public var txt_msg:smb_font;
      
      public function anm_fin_txt_2p_16()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_msg.SetTextSize(33);
         this.txt_msg.SetTextPivot(smb_font.CCD_PIVOT_RC);
      }
   }
}

