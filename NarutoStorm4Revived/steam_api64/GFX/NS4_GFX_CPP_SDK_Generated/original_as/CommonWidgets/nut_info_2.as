package script.net_match_2
{
   import flash.display.MovieClip;
   import script.net_icon.nut_info;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol17")]
   public dynamic class nut_info extends MovieClip
   {
      
      public var all_info_match:script.net_icon.nut_info;
      
      public var mc_prog:script.net_icon.nut_info;
      
      public var txt_info02:smb_font;
      
      public var txt_info01:smb_font;
      
      public var txt_info00:smb_font;
      
      public var txt_head02:smb_font;
      
      public var all_info_slot:script.net_icon.nut_info;
      
      public var txt_head01:smb_font;
      
      public var txt_head00:smb_font;
      
      public var all_host:script.net_icon.nut_info;
      
      public var txt_title:smb_font;
      
      public var mc_round:script.net_icon.nut_info;
      
      public var mc_stage:script.net_icon.nut_info;
      
      public function nut_info()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_title.SetTextColor(12305407);
         this.txt_title.SetTextSize(25);
         this.txt_head00.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_head00.SetTextSize(25);
         this.txt_info00.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_info00.SetTextSize(28);
         this.txt_head01.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_head01.SetTextSize(25);
         this.txt_info01.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_info01.SetTextSize(28);
         this.txt_head02.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_head02.SetTextSize(25);
         this.txt_info02.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_info02.SetTextSize(28);
      }
      
      internal function frame2() : *
      {
         stop();
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_title.SetTextColor(12305407);
         this.txt_title.SetTextSize(25);
         this.txt_head00.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_head00.SetTextSize(25);
         this.txt_info00.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_info00.SetTextSize(28);
         this.txt_head01.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_head01.SetTextSize(25);
         this.txt_info01.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_info01.SetTextSize(28);
      }
      
      internal function frame3() : *
      {
         stop();
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_title.SetTextColor(12305407);
         this.txt_title.SetTextSize(25);
         this.txt_head00.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_head00.SetTextSize(25);
         this.txt_info00.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_info00.SetTextSize(28);
      }
   }
}

