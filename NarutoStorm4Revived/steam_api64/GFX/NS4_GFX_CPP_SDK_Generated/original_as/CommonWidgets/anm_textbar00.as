package script.result_main
{
   import flash.display.MovieClip;
   import flash.geom.Point;
   import script.xcmn_font.smb_font;
   import script.xcp_frame_bar1.smb_frame_bar1_1;
   import script.xcp_frame_bar1.smb_frame_bar1_2;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol109")]
   public class anm_textbar00 extends MovieClip
   {
      
      public var mc_base_1:smb_frame_bar1_1;
      
      public var mc_base_2:smb_frame_bar1_2;
      
      public var txt_money00:smb_font;
      
      public var txt_money01:smb_font;
      
      public var txt_mult:smb_font;
      
      public var txt_pt:smb_font;
      
      public var txt_rslt:smb_font;
      
      public var txt_ryo:smb_font;
      
      private var m_txtRslt:smb_font = null;
      
      private var m_txtPt:smb_font = null;
      
      private var m_txtMult:smb_font = null;
      
      private var m_txtMoney_0:smb_font = null;
      
      private var m_txtMoney_1:smb_font = null;
      
      private var m_txtRyo:smb_font = null;
      
      private var m_isChangedLayout:Boolean = false;
      
      public function anm_textbar00()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2);
         this.m_txtRslt = this["txt_rslt"];
         this.m_txtPt = this["txt_pt"];
         this.m_txtMult = this["txt_mult"];
         this.m_txtMoney_0 = this["txt_money00"];
         this.m_txtMoney_1 = this["txt_money01"];
         this.m_txtRyo = this["txt_ryo"];
      }
      
      private function CheckArabicLayout() : Boolean
      {
         var _loc1_:MovieClip = null;
         var _loc2_:Point = null;
         var _loc3_:Point = null;
         var _loc4_:Number = NaN;
         if(this.m_txtRslt.IsArabic() == true)
         {
            if(this.m_isChangedLayout == false)
            {
               _loc1_ = this["mc_base_1"];
               if(_loc1_ != null)
               {
                  _loc4_ = _loc1_.x;
               }
               else
               {
                  _loc1_ = this["mc_base_2"];
                  if(_loc1_ != null)
                  {
                     _loc4_ = _loc1_.x;
                  }
               }
               _loc2_ = new Point();
               this.m_txtRslt.GetTextPos(_loc2_);
               this.m_txtRslt.SetTextPos(_loc2_.x + (_loc4_ - _loc2_.x) * 2,_loc2_.y);
               this.m_txtMoney_1.GetTextPos(_loc2_);
               this.m_txtMoney_1.SetTextPos(_loc2_.x + (_loc4_ - _loc2_.x) * 2,_loc2_.y);
               this.m_txtRyo.GetTextPos(_loc2_);
               this.m_txtRyo.SetTextPos(_loc2_.x + (_loc4_ - _loc2_.x) * 2,_loc2_.y);
               _loc3_ = new Point();
               this.m_txtMult.GetTextPos(_loc2_);
               this.m_txtMult.SetTextPos(_loc2_.x + (_loc4_ - _loc2_.x) * 2,_loc2_.y);
               this.m_txtPt.GetTextPos(_loc2_);
               this.m_txtMoney_0.GetTextPos(_loc3_);
               this.m_txtPt.SetTextPos(_loc3_.x + (_loc4_ - _loc3_.x) * 2,_loc2_.y);
               this.m_txtMoney_0.SetTextPos(_loc2_.x + (_loc4_ - _loc2_.x) * 2,_loc3_.y);
            }
            this.m_txtRslt.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_txtRslt.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.m_txtMoney_1.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_txtMoney_1.SetTextPivot(smb_font.CCD_PIVOT_LC);
            this.m_txtRyo.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_txtRyo.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.m_txtPt.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_txtMult.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_txtMoney_0.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_isChangedLayout = true;
         }
         return this.m_isChangedLayout;
      }
      
      internal function frame1() : *
      {
         this.stop();
         this.txt_rslt.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_rslt.SetTextSize(30);
         this.txt_rslt.SetTextFieldWidth(555);
         this.txt_rslt.SetTextFit(true);
         this.txt_rslt.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_rslt.DisableDropShadowFilter();
         this.txt_pt.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_pt.SetTextSize(22);
         this.txt_pt.SetTextColor(11049307);
         this.txt_pt.DisableDropShadowFilter();
         this.txt_mult.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_mult.SetTextSize(20);
         this.txt_mult.SetTextColor(10066329);
         this.txt_mult.DisableDropShadowFilter();
         this.txt_money00.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_money00.SetTextSize(22);
         this.txt_money00.SetTextFieldWidth(105);
         this.txt_money00.SetTextFit(true);
         this.txt_money00.SetTextColor(10066329);
         this.txt_money00.DisableDropShadowFilter();
         this.txt_money01.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_money01.SetTextSize(30);
         this.txt_money01.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_money01.DisableDropShadowFilter();
         this.txt_ryo.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_ryo.SetTextSize(25);
         this.txt_ryo.SetTextFieldWidth(60);
         this.txt_ryo.SetTextFit(true);
         this.txt_ryo.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_ryo.DisableDropShadowFilter();
         if(this.CheckArabicLayout() == true)
         {
            this.mc_base_1.scaleX *= -1;
         }
      }
      
      internal function frame2() : *
      {
         this.stop();
         this.txt_rslt.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_rslt.SetDropShadowFilter(2691849);
         this.txt_pt.SetTextColor(13745256);
         this.txt_pt.SetDropShadowFilter(2691849);
         this.txt_mult.SetTextColor(11119017);
         this.txt_mult.SetDropShadowFilter(2691849);
         this.txt_money00.SetTextColor(11119017);
         this.txt_money00.SetDropShadowFilter(2691849);
         this.txt_money01.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_money01.SetDropShadowFilter(2691849);
         this.txt_ryo.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_ryo.SetDropShadowFilter(2691849);
         if(this.CheckArabicLayout() == true)
         {
            this.mc_base_2.scaleX *= -1;
         }
      }
   }
}

