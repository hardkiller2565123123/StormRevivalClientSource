package net_match_2_fla
{
   import flash.display.MovieClip;
   import script.net_cmn.anm_msg;
   import script.net_icon.nut_type;
   import script.xcmn_font.smb_font;
   import script.xcmn_net.nut_icon_wave;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol4")]
   public dynamic class anm_id_6 extends MovieClip
   {
      
      public var all_status01:nut_type;
      
      public var all_status00:nut_type;
      
      public var txt_rank:smb_font;
      
      public var txt_num:smb_font;
      
      public var all_ok:anm_msg;
      
      public var txt_id:smb_font;
      
      public var all_icon_wave:nut_icon_wave;
      
      public function anm_id_6()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_id.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_id.SetTextSize(30);
         this.txt_id.SetTextFieldWidth(440);
         this.txt_id.SetTextFit(true);
         this.txt_rank.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_rank.SetTextSize(30);
         this.txt_rank.SetTextFieldWidth(120);
         this.txt_rank.SetTextFit(true);
         this.txt_num.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_num.SetTextSize(30);
         this.txt_num.SetTextFieldWidth(70);
         this.txt_num.SetTextFit(true);
      }
   }
}

