package script.duel_cmn
{
   import InputPad.InputPadKeyCode;
   import Select.UiSelect;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.external.*;
   import flash.geom.Point;
   import script.xcmn_font.smb_font;
   import script.xcmn_unset.*;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol284")]
   public class nut_cmdlist extends MovieClip
   {
      
      public var mc_cmd00:MovieClip;
      
      public var mc_cmd01:MovieClip;
      
      public var mc_line:MovieClip;
      
      public var mc_head:MovieClip;
      
      public var mc_scb:nut_scb_bg;
      
      public var GetTitle:Function;
      
      public var GetComboData:Function;
      
      public var GetListNum:Function;
      
      public var SetEnd:Function;
      
      public const DISP_NUM:int = 2;
      
      public const DISP_TYPE_COMMANDLIST:int = 0;
      
      public const DISP_TYPE_COMBOLIST:int = 1;
      
      internal var input:InputPadKeyCode = new InputPadKeyCode();
      
      internal var select:UiSelect = new UiSelect();
      
      internal var label:String;
      
      internal var disptype:int;
      
      internal var playerSide:int = 0;
      
      public function nut_cmdlist()
      {
         super();
         addFrameScript(4,this.frame5,9,this.frame10);
         this.visible = false;
      }
      
      public function Initialize() : void
      {
         var _loc2_:Point = null;
         this.visible = true;
         this.name = "all_cmblist";
         trace(this.name + " Initialize()");
         gotoAndPlay("in");
         this.label = "in";
         this.mc_head.txt_head.visible = false;
         this.mc_cmd00.txt_title.visible = false;
         this.mc_cmd00.txt_cmd.visible = false;
         this.mc_cmd00.txt_notes.visible = false;
         this.mc_cmd01.txt_title.visible = false;
         this.mc_cmd01.txt_cmd.visible = false;
         this.mc_cmd01.txt_notes.visible = false;
         var _loc1_:String = smb_font.CCD_ALIGN_LEFT;
         if(this.mc_cmd00.txt_title.IsArabic() == true)
         {
            _loc1_ = smb_font.CCD_ALIGN_RIGHT;
            _loc2_ = new Point();
            this.mc_cmd00.txt_title.GetTextPos(_loc2_);
            this.mc_cmd00.txt_title.SetTextPos(-_loc2_.x,_loc2_.y);
            this.mc_cmd00.txt_title.SetTextPivot(smb_font.CCD_PIVOT_RT);
            this.mc_cmd00.txt_cmd.GetTextPos(_loc2_);
            this.mc_cmd00.txt_cmd.SetTextPos(-_loc2_.x,_loc2_.y);
            this.mc_cmd00.txt_cmd.SetTextPivot(smb_font.CCD_PIVOT_RT);
            this.mc_cmd00.txt_notes.GetTextPos(_loc2_);
            this.mc_cmd00.txt_notes.SetTextPos(-_loc2_.x,_loc2_.y);
            this.mc_cmd00.txt_notes.SetTextPivot(smb_font.CCD_PIVOT_RT);
            this.mc_cmd01.txt_title.GetTextPos(_loc2_);
            this.mc_cmd01.txt_title.SetTextPos(-_loc2_.x,_loc2_.y);
            this.mc_cmd01.txt_title.SetTextPivot(smb_font.CCD_PIVOT_RT);
            this.mc_cmd01.txt_cmd.GetTextPos(_loc2_);
            this.mc_cmd01.txt_cmd.SetTextPos(-_loc2_.x,_loc2_.y);
            this.mc_cmd01.txt_cmd.SetTextPivot(smb_font.CCD_PIVOT_RT);
            this.mc_cmd01.txt_notes.GetTextPos(_loc2_);
            this.mc_cmd01.txt_notes.SetTextPos(-_loc2_.x,_loc2_.y);
            this.mc_cmd01.txt_notes.SetTextPivot(smb_font.CCD_PIVOT_RT);
         }
         this.mc_cmd00.txt_title.SetTextAlign(_loc1_);
         this.mc_cmd00.txt_cmd.SetTextAlign(_loc1_);
         this.mc_cmd00.txt_notes.SetTextAlign(_loc1_);
         this.mc_cmd01.txt_title.SetTextAlign(_loc1_);
         this.mc_cmd01.txt_cmd.SetTextAlign(_loc1_);
         this.mc_cmd01.txt_notes.SetTextAlign(_loc1_);
         addEventListener(Event.ENTER_FRAME,this.onEnterFrameCtrl);
      }
      
      private function onEnterFrameCtrl(param1:Event) : void
      {
         var _loc2_:int = 0;
         var _loc3_:String = null;
         var _loc4_:* = undefined;
         if(this.label == "in" && currentLabel == "loop")
         {
            trace("inAnm is end");
            this.label = currentLabel;
            this.mc_head.txt_head.visible = true;
            this.mc_cmd00.txt_title.visible = true;
            this.mc_cmd00.txt_cmd.visible = true;
            this.mc_cmd00.txt_notes.visible = true;
            this.mc_cmd01.txt_title.visible = true;
            this.mc_cmd01.txt_cmd.visible = true;
            this.mc_cmd01.txt_notes.visible = true;
            _loc2_ = this.GetListNum();
            trace("ListNum = " + _loc2_);
            this.select.InitSelect(0,0,_loc2_ - this.DISP_NUM,this.input.GetKeyInputBtn_L_Up(),this.input.GetKeyInputBtn_L_Down(),UiSelect.CCD_LOOP_TYPE_DISABLE);
            _loc3_ = this.GetTitle();
            this.mc_head.txt_head.SetText(_loc3_);
            this.updateComboData();
            this.mc_scb.SetRange(_loc2_,this.DISP_NUM,true);
            this.mc_scb.UpdateScroll(0);
         }
         if(this.label == "loop" && this.select != null)
         {
            _loc4_ = this.select.GetSelValue();
            this.select.SelectMenuCtrl();
            if(_loc4_ != this.select.GetSelValue())
            {
               ExternalInterface.call("RequestPlaySE_Select");
               this.mc_scb.UpdateScroll(this.select.GetSelValue());
               this.updateComboData();
            }
            else if(this.input.GetPadPress() & this.input.GetKeyInputBtn_Cancel())
            {
               ExternalInterface.call("RequestPlaySE_Cancel");
               this.setOut();
            }
         }
         if(this.label == "out")
         {
            trace("frame = " + currentFrame);
            if(currentFrame == totalFrames)
            {
               this.SetEnd();
               removeEventListener(Event.ENTER_FRAME,this.onEnterFrameCtrl);
            }
         }
      }
      
      private function updateComboData() : void
      {
         var _loc5_:Object = null;
         trace("top =" + this.select.GetSelValue());
         var _loc1_:Array = new Array(2);
         var _loc2_:int = 0;
         while(_loc2_ < _loc1_.length)
         {
            _loc5_ = new Object();
            _loc5_.title = "";
            _loc5_.command = "";
            _loc5_.notes = "";
            _loc1_[_loc2_] = _loc5_;
            _loc2_++;
         }
         this.GetComboData(this.select.GetSelValue(),_loc1_);
         this.mc_cmd00.txt_title.SetText(_loc1_[0].title);
         this.mc_cmd00.txt_cmd.SetPlayerSide(this.playerSide);
         this.mc_cmd00.txt_cmd.SetTextFieldWidth(1200);
         this.mc_cmd00.txt_cmd.SetText(_loc1_[0].command);
         this.mc_cmd00.txt_notes.SetText(_loc1_[0].notes);
         var _loc3_:Point = new Point();
         this.mc_cmd00.txt_cmd.GetTextPos(_loc3_);
         var _loc4_:Point = new Point();
         this.mc_cmd00.txt_notes.GetTextPos(_loc4_);
         this.mc_cmd00.txt_notes.SetTextPos(_loc3_.x,_loc4_.y);
         this.mc_cmd01.txt_title.SetText(_loc1_[1].title);
         this.mc_cmd01.txt_cmd.SetPlayerSide(this.playerSide);
         this.mc_cmd01.txt_cmd.SetTextFieldWidth(1200);
         this.mc_cmd01.txt_cmd.SetText(_loc1_[1].command);
         this.mc_cmd01.txt_notes.SetText(_loc1_[1].notes);
         this.mc_cmd01.txt_cmd.GetTextPos(_loc3_);
         this.mc_cmd01.txt_notes.GetTextPos(_loc4_);
         this.mc_cmd01.txt_notes.SetTextPos(_loc3_.x,_loc4_.y);
      }
      
      private function setOut() : void
      {
         trace("play anm [out]");
         gotoAndPlay("out");
         this.label = "out";
         this.mc_head.txt_head.visible = false;
         this.mc_cmd00.txt_title.visible = false;
         this.mc_cmd00.txt_cmd.visible = false;
         this.mc_cmd00.txt_notes.visible = false;
         this.mc_cmd01.txt_title.visible = false;
         this.mc_cmd01.txt_cmd.visible = false;
         this.mc_cmd01.txt_notes.visible = false;
      }
      
      public function setDispType(param1:int) : *
      {
         trace("c++ call setDispType( " + param1 + " )");
         this.disptype = param1;
         switch(this.disptype)
         {
            case this.DISP_TYPE_COMBOLIST:
               this.mc_head.gotoAndStop("1p");
               this.mc_cmd00.gotoAndStop("1p");
               this.mc_cmd01.gotoAndStop("1p");
               break;
            case this.DISP_TYPE_COMMANDLIST:
               this.mc_head.gotoAndStop("2p");
               this.mc_cmd00.gotoAndStop("2p");
               this.mc_cmd01.gotoAndStop("2p");
         }
      }
      
      public function setPlayerSide(param1:int) : *
      {
         this.playerSide = param1;
      }
      
      internal function frame5() : *
      {
         this.stop();
      }
      
      internal function frame10() : *
      {
         this.stop();
      }
   }
}

