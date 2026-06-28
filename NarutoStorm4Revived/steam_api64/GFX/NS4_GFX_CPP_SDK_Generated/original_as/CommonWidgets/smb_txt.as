package script.net_bonus
{
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   import flash.geom.Point;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_base;
   import script.xcmn_menu.nut_sel1;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol13")]
   public class smb_txt extends MovieClip
   {
      
      public var all_base:nut_base;
      
      public var all_sel1:nut_sel1;
      
      public var txt_get1:smb_font;
      
      public var txt_get2:smb_font;
      
      public var txt_title:smb_font;
      
      private var m_title:smb_font = null;
      
      private var m_getMsg1:smb_font = null;
      
      private var m_getMsg2:smb_font = null;
      
      public function smb_txt()
      {
         super();
         addFrameScript(0,this.frame1);
         this.m_title = this["txt_title"];
         this.m_getMsg1 = this["txt_get1"];
         this.m_getMsg2 = this["txt_get2"];
         this.m_title.SetText(String(ExternalInterface.call("MessageConvert","network_sys_195")));
      }
      
      public function SetContinuousLoginsNum(param1:int) : *
      {
         var _loc2_:Array = new Array();
         _loc2_.push(param1.toString());
         this.m_title.ReplaceTextList(_loc2_);
      }
      
      public function SetLoginGetItem(param1:String, param2:int) : *
      {
         var _loc3_:Array = new Array();
         _loc3_.push(param1);
         var _loc4_:String = param2.toString();
         if(this.m_getMsg1.IsArabic() == true)
         {
            _loc4_ = String.fromCharCode(8207) + _loc4_;
         }
         _loc3_.push(_loc4_);
         this.m_getMsg1.SetText(String(ExternalInterface.call("MessageConvert","network_sys_196")),_loc3_);
      }
      
      public function SetSpecialLoginBonus(param1:String, param2:int) : *
      {
         var _loc3_:Array = null;
         if(param2 == 0)
         {
            this.m_getMsg2.SetText(String(ExternalInterface.call("MessageConvert","networkmode_679")));
         }
         else
         {
            _loc3_ = new Array();
            _loc3_.push(param1);
            _loc3_.push(param2.toString());
            this.m_getMsg2.SetText(String(ExternalInterface.call("MessageConvert","network_sys_197")),_loc3_);
         }
      }
      
      public function SetEnableSelectMode() : *
      {
         this.m_getMsg2.visible = false;
         this.m_getMsg1.SetTextPivot(smb_font.CCD_PIVOT_CT);
         var _loc1_:Point = new Point();
         this.m_getMsg1.GetTextPos(_loc1_);
         this.m_getMsg1.SetTextPos(_loc1_.x,_loc1_.y - 20);
      }
      
      public function SetSelectItemInfo(param1:int, param2:String, param3:int, param4:Boolean) : *
      {
         var _loc5_:String = "networkmode_639";
         if(param4 == false)
         {
            _loc5_ = "networkmode_640";
         }
         var _loc6_:Array = new Array();
         _loc6_.push(param1.toString());
         _loc6_.push(param2);
         _loc6_.push(param3.toString());
         this.m_getMsg1.SetText(String(ExternalInterface.call("MessageConvert",_loc5_)),_loc6_);
      }
      
      internal function frame1() : *
      {
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_title.SetTextColor(16774492);
         this.txt_title.SetDropShadowFilter(6161478);
         this.txt_get1.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_get1.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_get1.SetTextFieldWidth(850);
         this.txt_get1.SetTextFit(true);
         this.txt_get2.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_get2.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_get2.SetTextFieldWidth(850);
         this.txt_get2.SetTextFit(true);
      }
   }
}

